#include "Oculus.h"

#include "Shader.h"
#include "MatrixStack.h"
#include "Sphere.h"
#include "Plane.h"
#include "Box.h"
#include "Cylinder.h"
#include "Texture.h"
#include "Passive3D.h"

//#define GLFW_EXPOSE_NATIVE_WIN32
//#define GLFW_EXPOSE_NATIVE_WGL

using namespace std;

// ------- Function declerations --------
//! Sets up a glfw window depending on the resolution of the Oculus Rift device
static void WindowSizeCallback(GLFWwindow* p_Window, int p_Width, int p_Height);
void GLRenderCallsOculus();

// Declare moveMesh - used for moving around the mesh in the scene.
// TODO: refactor this function to TOOLS namespace?
void moveMesh(Device* wand, Mesh* mTest, bool buttonPressed, float* changePos, float* differenceR);
void print_GLM_matrix(glm::mat4 M);
void print_FLOAT_matrix(float* M);

// --- Variable Declerations ------------
const bool L_MULTISAMPLING = false;
const int G_DISTORTIONCAPS = 0
| ovrDistortionCap_Vignette
| ovrDistortionCap_Chromatic
| ovrDistortionCap_Overdrive
//| ovrDistortionCap_TimeWarp // Turning this on gives ghosting???
;

ovrHmd hmd;
ovrGLConfig g_Cfg;
ovrEyeRenderDesc g_EyeRenderDesc[2];
ovrVector3f g_EyeOffsets[2];
ovrPosef g_EyePoses[2];
ovrTexture g_EyeTextures[2];
OVR::Matrix4f g_ProjectionMatrix[2];
OVR::Sizei g_RenderTargetSize;
ovrVector3f g_CameraPosition;

const float EYEHEIGHT{ OVR_DEFAULT_EYE_HEIGHT };
// --------------------------------------

int Oculus::runOvr() {

	GLfloat I[16] = { 1.0f, 0.0f, 0.0f, 0.0f,
					  0.0f, 1.0f, 0.0f, 0.0f,
					  0.0f, 0.0f, 1.0f, 0.0f,
					  0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat P[16] = { 2.42f, 0.0f, 0.0f, 0.0f,
					  0.0f, 2.42f, 0.0f, 0.0f,
					  0.0f, 0.0f, -1.0f, -1.0f,
					  0.0f, 0.0f, -0.2f, 0.0f };

	// Lightposition 
	GLfloat lightPos[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
	GLfloat lightPosTemp[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	//glm::vec4 lightPos = { 0.0f, 0.5f, 2.0f, 1.0f };
	glm::vec4 LP = glm::vec4(0);

	// Save old positions and transforms
	float changePos[3] = { 0.0f };
	float differenceR[16] = { 0.0f };
	float lastPos[3] = { 0.0f, 0.0f, 0.0f };
	float currPos[3] = { 0.0f, 0.0f, 0.0f };

	// Switch case variables
	int chooseFunction = 1;
	const int newDILATE = 1;
	const int UPDATE_VERTEX_ARRAY = 0;
	const int MOVE = 2;
	const int RECENTER = 3;
	const int coREGISTER = 4;

	// Co-register variables
	int regCounter = 0;
	bool renderRegisterSpheres = false;

	//float regSpherePos[16] =	{ 0.0f, 1.0f, 1.0f, 1.0f,	// Sp1
	//							-1.0f, -0.5f, 0.0f, 0.0f,	// Sp2
	//							0.0f, 0.0f, -0.5f, 0.5f,	// Sp3
	//							1.0f, 1.0f, 1.0f, 1.0f };	// Sp4

	//float regSpherePos[16] =   { 0.2f,  0.4f, 0.2f, 0.4f,	// Sp1 0.2
	//							-0.05f,  0.0f, -0.5f, -0.4f,	// Sp2 0.5
	//							0.05f,  -0.3f,-0.4f, 0.0f,	// Sp3 0.45
	//							1.0f, 1.0f, 1.0f, 1.0f };	// Sp4

	float regSpherePos[16] = { 0.0f, 0.0f, 0.4f, 0.4f,	// Sp1 0.2
								0.0f, -0.4f, 0.0f, -0.4f,	// Sp2 0.5
								-0.1f, -0.3f, -0.3f, -0.1f,	// Sp3 0.45
								1.0f, 1.0f, 1.0f, 1.0f };	// Sp4

	//float regSpherePos[16] =   { 0.0f, 1.0f,  0.0f, 1.0f,	// Sp1 1.0
	//							-0.05f, 0.6f, -0.5f, 0.4f,	// Sp2 1.1
	//							0.25f, -0.3f, -0.5f, 0.05f,	// Sp3 0.305
	//							1.0f, 1.0f, 1.0f, 1.0f };	// Sp4


	//
	float pos[16] = { 0.0f };
	float transform[16] = { 0.0f };
	float invPos[16] = { 0.0f };
	float eyeHeight = OVR_DEFAULT_EYE_HEIGHT;
	float eye, floor;


	// FPS
	double fps = 0;

	// Translation vector -- used for tranlate objects in SceneGraph
	float translateVector[3] = { 0.0f, 0.0f, 0.0f };

	// Size of the wand tool
	float wandRadius = 0.05f;
	
	//
	glm::vec4 nullVec = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	glm::vec4 tempVec = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	// States
	bool buttonPressed = false;
	bool buttonHeld = false;
	bool buttonReleased = false;
	bool lines = false;

	// Location used for UNIFORMS in shader
	GLint locationLP;
	GLint locationP;
	GLint locationMV;
	GLint locationOMV;
	GLint locationTex;

	//INITIALIZE OVR /////////////////////////////////////////////////////
	ovr_Initialize();
	int det;
	// Check for attached head mounted display...
	hmd = ovrHmd_Create(0);
	if (!hmd) {
		printf("No Oculus Rift device attached, using virtual version...\n");
		hmd = ovrHmd_CreateDebug(ovrHmd_DK2);

		det = ovrHmd_Detect();
		cout << det << endl;
	}

	// Check to see if we are running in "Direct" or "Extended Desktop" mode...
	bool l_DirectMode = ((hmd->HmdCaps & ovrHmdCap_ExtendDesktop) == 0);

	// INITIALIZE GL ////////////////////////////////////////////////////
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return 1;
	}

	if (L_MULTISAMPLING) glfwWindowHint(GLFW_SAMPLES, 4); 
	else glfwWindowHint(GLFW_SAMPLES, 0);


	// SETUP GLFW WINDOW AND CONTEXT /////////////////////////////////////////////////////////////
	// Create a window...
	GLFWwindow* l_Window;
	GLFWmonitor* l_Monitor;
	ovrSizei l_ClientSize;

	if (l_DirectMode) {
		printf("Running in \"Direct\" mode...\n");
		l_Monitor = NULL;

		l_ClientSize.w = hmd->Resolution.w; // Something reasonable, smaller, but maintain aspect ratio...
		l_ClientSize.h = hmd->Resolution.h; // Something reasonable, smaller, but maintain aspect ratio...
	} else {// Extended Desktop mode...
		printf("Running in \"Extended Desktop\" mode...\n");
		int l_Count;
		GLFWmonitor** l_Monitors = glfwGetMonitors(&l_Count);
		switch (l_Count) {
		  case 0: {
		    printf("No monitors found, exiting...\n");
			exit(EXIT_FAILURE);
			break;
		  }
		  case 1: {
			printf("Two monitors expected, found only one, using primary...\n");
			l_Monitor = glfwGetPrimaryMonitor();
			break;
		  }
		  case 2: {
			printf("Two monitors found, using second monitor...\n");
			l_Monitor = l_Monitors[1];
			break;
		  }
		  default: {
			printf("More than two monitors found, using second monitor...\n");
			l_Monitor = l_Monitors[1];
		  }
		}

		l_ClientSize.w = hmd->Resolution.w; // 1920 for DK2...
		l_ClientSize.h = hmd->Resolution.h; // 1080 for DK2...
	}

	l_Window = glfwCreateWindow(l_ClientSize.w, l_ClientSize.h, "GLFW Oculus Rift Test", l_Monitor, NULL);

	// Check if window creation was succesfull...
	if (!l_Window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// Attach the window in "Direct Mode"...
#if defined(_WIN32)
	if (l_DirectMode) {
		ovrBool l_AttachResult = ovrHmd_AttachToWindow(hmd, glfwGetWin32Window(l_Window), NULL, NULL);
		if (!l_AttachResult) {
			printf("Could not attach to window...");
			exit(EXIT_FAILURE);
		}
	}
#endif

	// Make the context current for this window...
	glfwMakeContextCurrent(l_Window);

	//start GLEW extension handler
	glewExperimental = GL_TRUE;
	GLenum l_GlewResult = glewInit();
	if (l_GlewResult != GLEW_OK) {
		printf("glewInit() error.\n");
		exit(EXIT_FAILURE);
	}

	// Print some info about the OpenGL context...
	int l_Major = glfwGetWindowAttrib(l_Window, GLFW_CONTEXT_VERSION_MAJOR);
	int l_Minor = glfwGetWindowAttrib(l_Window, GLFW_CONTEXT_VERSION_MINOR);
	int l_Profile = glfwGetWindowAttrib(l_Window, GLFW_OPENGL_PROFILE);
	printf("OpenGL: %d.%d ", l_Major, l_Minor);
	if (l_Major >= 3) { // Profiles introduced in OpenGL 3.0...
		if (l_Profile == GLFW_OPENGL_COMPAT_PROFILE) printf("GLFW_OPENGL_COMPAT_PROFILE\n"); else printf("GLFW_OPENGL_CORE_PROFILE\n");
	}
	printf("Vendor: %s\n", (char*)glGetString(GL_VENDOR));
	printf("Renderer: %s\n", (char*)glGetString(GL_RENDERER));

	//CREATE OCULUS TEXTURES AND BIND THESE TO GL///////////////////////////////////////////////////////////////////////////////
	ovrSizei l_EyeTextureSizes[2];

	l_EyeTextureSizes[ovrEye_Left] = ovrHmd_GetFovTextureSize(hmd, ovrEye_Left, hmd->MaxEyeFov[ovrEye_Left], 1.0f);
	l_EyeTextureSizes[ovrEye_Right] = ovrHmd_GetFovTextureSize(hmd, ovrEye_Right, hmd->MaxEyeFov[ovrEye_Right], 1.0f);

	// Combine for one texture for both eyes...
	g_RenderTargetSize.w = l_EyeTextureSizes[ovrEye_Left].w + l_EyeTextureSizes[ovrEye_Right].w;
	g_RenderTargetSize.h = (l_EyeTextureSizes[ovrEye_Left].h>l_EyeTextureSizes[ovrEye_Right].h ? l_EyeTextureSizes[ovrEye_Left].h : l_EyeTextureSizes[ovrEye_Right].h);

	// Create the FBO being a single one for both eyes (this is open for debate)...
	GLuint l_FBOId;
	glGenFramebuffers(1, &l_FBOId);
	glBindFramebuffer(GL_FRAMEBUFFER, l_FBOId);

	// The texture we're going to render to...
	GLuint l_TextureId;
	glGenTextures(1, &l_TextureId);
	// "Bind" the newly created texture : all future texture functions will modify this texture...
	glBindTexture(GL_TEXTURE_2D, l_TextureId);
	// Give an empty image to OpenGL (the last "0")
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, g_RenderTargetSize.w, g_RenderTargetSize.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	// Linear filtering...
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// Create Depth Buffer...
	GLuint l_DepthBufferId;
	glGenRenderbuffers(1, &l_DepthBufferId);
	glBindRenderbuffer(GL_RENDERBUFFER, l_DepthBufferId);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, g_RenderTargetSize.w, g_RenderTargetSize.h);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, l_DepthBufferId);

	// Set the texture as our colour attachment #0...
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, l_TextureId, 0);

	// Set the list of draw buffers...
	GLenum l_GLDrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, l_GLDrawBuffers); // "1" is the size of DrawBuffers

	// Check if everything is OK...
	GLenum l_Check = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
	if (l_Check != GL_FRAMEBUFFER_COMPLETE) {
		printf("There is a problem with the FBO.\n");
		exit(EXIT_FAILURE);
	}

	// Unbind...
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// SETUP TEXTURES FOR EACH EYE /////////////////////////////////////////////////////////////////////
	// Left eye...
	g_EyeTextures[ovrEye_Left].Header.API = ovrRenderAPI_OpenGL;
	g_EyeTextures[ovrEye_Left].Header.TextureSize = g_RenderTargetSize;
	g_EyeTextures[ovrEye_Left].Header.RenderViewport.Pos.x = 0;
	g_EyeTextures[ovrEye_Left].Header.RenderViewport.Pos.y = 0;
	g_EyeTextures[ovrEye_Left].Header.RenderViewport.Size = l_EyeTextureSizes[ovrEye_Left];
	((ovrGLTexture&)(g_EyeTextures[ovrEye_Left])).OGL.TexId = l_TextureId;

	// Right eye (mostly the same as left but with the viewport on the right side of the texture)
	g_EyeTextures[ovrEye_Right] = g_EyeTextures[ovrEye_Left];
	g_EyeTextures[ovrEye_Right].Header.RenderViewport.Pos.x = (g_RenderTargetSize.w + 1) / 2;
	g_EyeTextures[ovrEye_Right].Header.RenderViewport.Pos.y = 0;

	// OCULUS RIFT EYE CONFIGURATIONS
	g_Cfg.OGL.Header.API = ovrRenderAPI_OpenGL;
	g_Cfg.OGL.Header.BackBufferSize.w = l_ClientSize.w;
	g_Cfg.OGL.Header.BackBufferSize.h = l_ClientSize.h;
	g_Cfg.OGL.Header.Multisample = (L_MULTISAMPLING ? 1 : 0);

	g_Cfg.OGL.Window = glfwGetWin32Window(l_Window);
	g_Cfg.OGL.DC = GetDC(g_Cfg.OGL.Window);

	// Enable capabilities...
	// ovrHmd_SetEnabledCaps(hmd, ovrHmdCap_LowPersistence | ovrHmdCap_DynamicPrediction);

	ovrBool l_ConfigureResult = ovrHmd_ConfigureRendering(hmd, &g_Cfg.Config, G_DISTORTIONCAPS, hmd->MaxEyeFov, g_EyeRenderDesc);
	if (!l_ConfigureResult) {
		printf("Configure failed.\n");
		exit(EXIT_FAILURE);
	}

	// Start the sensor which provides the Rift’s pose and motion...
	uint32_t l_SupportedSensorCaps = ovrTrackingCap_Orientation | ovrTrackingCap_MagYawCorrection | ovrTrackingCap_Position;
	uint32_t l_RequiredTrackingCaps = 0;
	ovrBool l_TrackingResult = ovrHmd_ConfigureTracking(hmd, l_SupportedSensorCaps, l_RequiredTrackingCaps);
	if (!l_TrackingResult) {
		printf("Could not start tracking...");
		exit(EXIT_FAILURE);
	}

	// set projection matrix for each eye
	g_ProjectionMatrix[ovrEye_Left] = ovrMatrix4f_Projection(g_EyeRenderDesc[ovrEye_Left].Fov, 0.3f, 100.0f, true);
	g_ProjectionMatrix[ovrEye_Right] = ovrMatrix4f_Projection(g_EyeRenderDesc[ovrEye_Right].Fov, 0.3f, 100.0f, true);

	// set IPD offset values
	g_EyeOffsets[ovrEye_Left] = g_EyeRenderDesc[ovrEye_Left].HmdToEyeViewOffset;
	g_EyeOffsets[ovrEye_Right] = g_EyeRenderDesc[ovrEye_Right].HmdToEyeViewOffset;

	//glfwSetKeyCallback(l_Window, KeyCallback);
	glfwSetWindowSizeCallback(l_Window, WindowSizeCallback);

	//DECLARE AND CREATE SHADERS ///////////////////////////////////////////////////////////////////////////////////
	Shader phongShader;
	phongShader.createShader("vertexshader.glsl", "fragmentshader.glsl");

	// CREATE MATRIX STACK
	MatrixStack MVstack;
	MVstack.init();
	
	//DECLARE SCENE OBJECTS ///////////////////////////////////////////////////////////////////////////////////
	Sphere light(glm::vec3(0.0f, 0.0f, 0.0f), 0.05f);								// Sphere used for show light source in scene.
	Sphere regSphere(glm::vec3(0.0f, 0.0f, 0.0f), 0.05f);							// Sphere used for co-registration.

	Plane ground(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(100.0f, 100.0f));			//Ground plane
	Box box(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.46f, 0.46f, 0.53f));
	Box boxCamera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.15f, 1.58f, 0.15f));

	// Wand = Box + sphere
	Box boxWand(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.20f, 0.03f, 0.03f));
	Sphere sphereWand(glm::vec3(0.0f, 0.0f, 0.0f), 1.0f);

	// Mesh
	Mesh* mTest = new Mesh();

	// Initilise VRPN connection with the Intersense wand
	Device* wand = new Device(true, true, false, "Mouse");
	//Device* wand = new Device(true, true, true, "Wand");

	wand3d::Wand3dObserver* wand3d = new Passive3D();

	// TEXTURES ///////////////////////////////////////////////////////////////////////////////////////////////
	glEnable(GL_TEXTURE_2D);
	// Wand function textures
	Texture move("../Textures/test1.DDS");
	Texture dilate("../Textures/test3.DDS");
	Texture erode("../Textures/test5.DDS");
	Texture dnp("../Textures/blue3.DDS");

	Texture groundTex("x.DDS");
	Texture meshTex("x.DDS");
	Texture boxTex("x.DDS");

	GLuint currentTexID = move.getTextureID();

	//UNIFORM VARIABLES WITH SHADER ///////////////////////////////////////////////////////////////////////////
	locationMV = glGetUniformLocation(phongShader.programID, "MV");						// ModelView Matrix
	locationOMV = glGetUniformLocation(phongShader.programID, "OMV");					//
	locationP = glGetUniformLocation(phongShader.programID, "P");						// Perspective Matrix
	locationLP = glGetUniformLocation(phongShader.programID, "lightPos");				// Light position
	locationTex = glGetUniformLocation(phongShader.programID, "tex");					// Texture Matrix

	//ovrHmd_RecenterPose(hmd);
	ovrHmd_DismissHSWDisplay(hmd); // dismiss health safety warning

	// Main loop...
	unsigned int l_FrameIndex = 0;
	// RENDER LOOP ////////////////////////////////////////////////////////////////////////////////////////
	while (!glfwWindowShouldClose(l_Window)) {
		// Show fps at the top of the window
		fps = Utilities::displayFPS(l_Window);

		// STATES //////////////////////////////////////////////////////////////////////////////////////////////
		// All states are originally false
		if (wand->getButtonState() && !buttonPressed && !buttonHeld) { // Button pressed
			buttonPressed = true;
		}
		else if (!wand->getButtonState()) { // Button released
			buttonReleased = buttonHeld;
			buttonHeld = false;
		}
		else if (buttonPressed || buttonHeld) { // Button held down
			buttonHeld = true;
			buttonPressed = false;
		}
		
		// INTERACTION ////////////////////////////////////////////////////////////////////////////////////////
		if (buttonPressed || buttonHeld) {
			switch (wand->getButtonNumber()) {
			case 0: // Dilate/Erosion, 2nd from the left
				//chooseFunction = UPDATE_VERTEX_ARRAY;
				currentTexID = dilate.getTextureID(); // erode later
				break;
			case 1: //Drag&Pull, first from the left		
				chooseFunction = newDILATE;
				//cout << "X: " << wand3d->getWandOrientation()[0] << "Y: " << wand3d->getWandOrientation()[1] << "Z: " << wand3d->getWandOrientation()[2] << endl;
				currentTexID = dnp.getTextureID();
				break;
			case 2: // Move, 2nd from the right
				//chooseFunction = MOVE;
				currentTexID = move.getTextureID();
				moveMesh(wand, mTest, buttonPressed, changePos, differenceR);
				break;
			case 3: // Recenter, first from the right
				//chooseFunction = RECENTER;
				break;
			case 4: // co-register, analog button
				chooseFunction = coREGISTER;
				ovrHmd_RecenterPose(hmd);
				ovrHmd_DismissHSWDisplay(hmd);
				renderRegisterSpheres = true;
				wand->setTransformMatrix(I);
				break;
			case 5: // Use chosen function
				if (chooseFunction == UPDATE_VERTEX_ARRAY) {
					//mTest->updateVertexArray(wand->getTrackerPosition(), false, wandRadius);
				}
				else if (chooseFunction == newDILATE) {
					mTest->dilate(wand->getTrackerPosition(), lastPos, wandRadius, true);
				}
				else if (chooseFunction == coREGISTER && buttonPressed) {

					if (regCounter <= 3)
					{
						for (int i = 0; i < 3; i++) { // Save wand position & rotation 
							pos[i * 4 + regCounter] = wand->getTrackerPosition()[i];
						}
						cout << endl;
						pos[12 + regCounter] = 1.0f; // column --> sista raden med ettor
					}
					if (regCounter == 3) {
						// transform = regSpherePos * invPos    ------   transform * pos = regSpherePos
						// (M1, M2, Mout) -> Mout = M2 * M1
						Utilities::invertMatrix(pos, invPos);
						Utilities::matrixMult(invPos, regSpherePos, transform);
						wand->setTransformMatrix(transform);
						renderRegisterSpheres = false;
					}
					else if (regCounter == 4)
						eye = wand->getTrackerPosition()[1];		// ta ögon höjd		regCounter = 4
					else if (regCounter == 5)
						floor = wand->getTrackerPosition()[1];	// ta golv höjd		regCounter = 5

					regCounter++;
					if (regCounter == 6)						// Configure done.
					{
						eyeHeight = eye - floor;
						regCounter = 0;
						chooseFunction = newDILATE;
					}
				}
				break;
			default:
				chooseFunction = -1;
			}
		}


		// ANALOG BUTTON - change tool size
		if (wand->getAnalogPosition()[0] != 0 || wand->getAnalogPosition()[1] != 0) {

			const float MAX_RADIUS_WAND_TOOL = 0.2f;
			const float MIN_RADIUS_WAND_TOOL = 0.02f;

			// check if tool is to small or to big
			if (wandRadius > MIN_RADIUS_WAND_TOOL && wandRadius < MAX_RADIUS_WAND_TOOL) {
				wandRadius += 0.001f*wand->getAnalogPosition()[1];
			}
			else if (wandRadius <= MIN_RADIUS_WAND_TOOL && wand->getAnalogPosition()[1] > 0) {
				wandRadius += 0.001f*wand->getAnalogPosition()[1];
			}
			else if (wandRadius >= MAX_RADIUS_WAND_TOOL && wand->getAnalogPosition()[1] < 0) {
				wandRadius += 0.001f*wand->getAnalogPosition()[1];
			}
		}


		// KEYBORD EVENTS
		if (glfwGetKey(l_Window, GLFW_KEY_O)) {
			ovrHmd_RecenterPose(hmd);
			ovrHmd_DismissHSWDisplay(hmd);
		}
		if (glfwGetKey(l_Window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(l_Window, GL_TRUE);
		}
		if (glfwGetKey(l_Window, GLFW_KEY_Q)) {
			wandRadius += 0.01f;
		}
		if (glfwGetKey(l_Window, GLFW_KEY_W)) {
			wandRadius -= 0.01f;
		}
		if (glfwGetKey(l_Window, GLFW_KEY_R)) {
			delete mTest; // Reset mesh
			mTest = new Mesh();
		}
		// Activate wireframe (hold L)
		if (glfwGetKey(l_Window, GLFW_KEY_L) == GLFW_PRESS && !lines) {
			lines = true;
		}
		else if (glfwGetKey(l_Window, GLFW_KEY_L) == GLFW_RELEASE && lines){
			lines = false;
		}
		// Reset offset when button is released
		/*if (buttonReleased) {
			changePos[0] = 0.0f;
			changePos[1] = 0.0f;
			changePos[2] = 0.0f;
			Utilities::makeUniform(differenceR);
		}*/
		///////////////////////////////////////////////////////////////////////////////////////////////////////
		// Save position of tracker from last frame to get deltaPos
		lastPos[0] = wand->getTrackerPosition()[0];
		lastPos[1] = wand->getTrackerPosition()[1];
		lastPos[2] = wand->getTrackerPosition()[2];

		// Begin the frame...
		ovrHmd_BeginFrame(hmd, l_FrameIndex);

		// Get eye poses for both the left and the right eye. g_EyePoses contains all Rift information: orientation, positional tracking and
		// the IPD in the form of the input variable g_EyeOffsets.
		ovrHmd_GetEyePoses(hmd, l_FrameIndex, g_EyeOffsets, g_EyePoses, NULL);

		// Bind the FBO...
		glBindFramebuffer(GL_FRAMEBUFFER, l_FBOId);

		GLRenderCallsOculus();
		if (lines) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else if (!lines) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		
		for (int l_EyeIndex = 0; l_EyeIndex<ovrEye_Count; l_EyeIndex++) {

			ovrEyeType l_Eye = hmd->EyeRenderOrder[l_EyeIndex];

			glViewport(g_EyeTextures[l_Eye].Header.RenderViewport.Pos.x,
					   g_EyeTextures[l_Eye].Header.RenderViewport.Pos.y,
					   g_EyeTextures[l_Eye].Header.RenderViewport.Size.w,
					   g_EyeTextures[l_Eye].Header.RenderViewport.Size.h);

			glUseProgram(phongShader.programID);

			// Pass projection matrix on to OpenGL...
			glUniformMatrix4fv(locationP, 1, GL_FALSE, &(g_ProjectionMatrix[l_Eye].Transposed().M[0][0]));

			glUniform1i(locationTex, 0);

			// SCENEGRAPH //////////////////////////////////////////////////////////////////////////////////////////
			// Oculus transformations
			MVstack.push();
				// Multiply with orientation retrieved from sensor...
				OVR::Quatf l_Orientation = OVR::Quatf(g_EyePoses[l_Eye].Orientation);
				OVR::Matrix4f l_ModelViewMatrix = OVR::Matrix4f(l_Orientation.Inverted());

				MVstack.multiply(&(l_ModelViewMatrix.Transposed().M[0][0]));

				// LIGHT //////////////////////////////////////////////////////////////////////////////////////////
				//glm::mat4 pmat4 = glm::transpose(glm::make_mat4(MVstack.getCurrentMatrix()));
				glm::mat4 pmat4 = glm::make_mat4(MVstack.getCurrentMatrix());
				LP = pmat4 * glm::vec4(lightPos[0], lightPos[1], lightPos[2], 1.0f);

				lightPosTemp[0] = LP.x;
				lightPosTemp[1] = LP.y;
				lightPosTemp[2] = LP.z;
				lightPosTemp[3] = 1.0f;
				glUniform4fv(locationLP, 1, lightPosTemp);


				//!-- Translation due to positional tracking (DK2) and IPD...
				//glTranslatef(-g_EyePoses[l_Eye].Position.x, -g_EyePoses[l_Eye].Position.y, -g_EyePoses[l_Eye].Position.z);
				float eyePoses[3] = { -g_EyePoses[l_Eye].Position.x, -g_EyePoses[l_Eye].Position.y, -g_EyePoses[l_Eye].Position.z };
				MVstack.translate(eyePoses);
				glUniformMatrix4fv(locationMV, 1, GL_FALSE, MVstack.getCurrentMatrix());
		
				// Ground
				MVstack.push();
					translateVector[0] = 0.0f;
					translateVector[1] = -eyeHeight;
					translateVector[2] = 0.0f;
					MVstack.translate(translateVector);
					glUniformMatrix4fv(locationMV, 1, GL_FALSE, MVstack.getCurrentMatrix());
					//glBindTexture(GL_TEXTURE_2D, uniqueTexture.getTexID());
					ground.render();
				MVstack.pop();

				// Box camera
				MVstack.push();
					translateVector[0] = 0.0f;
					translateVector[1] = -eyeHeight + boxCamera.getDim().y / 2; // chair height
					translateVector[2] = -2.0f;
					MVstack.translate(translateVector);
					glUniformMatrix4fv(locationMV, 1, GL_FALSE, MVstack.getCurrentMatrix());
					//glBindTexture(GL_TEXTURE_2D, uniqueTexture.getTexID());
					boxCamera.render();
				MVstack.pop();

				// Box (chair) with wand on
				MVstack.push();
					translateVector[0] = 1.0f;
					translateVector[1] = -eyeHeight + box.getDim().y / 2; // chair height
					translateVector[2] = 0.0f;
					MVstack.translate(translateVector);
					glUniformMatrix4fv(locationMV, 1, GL_FALSE, MVstack.getCurrentMatrix());
					//glBindTexture(GL_TEXTURE_2D, uniqueTexture.getTexID());
					box.render();
				MVstack.pop();
	
				// Co-register spheres
				if (renderRegisterSpheres) {
					MVstack.push();
						translateVector[0] = regSpherePos[0 + regCounter];
						translateVector[1] = regSpherePos[4 + regCounter];
						translateVector[2] = regSpherePos[8 + regCounter];
						MVstack.translate(translateVector);
						glUniformMatrix4fv(locationMV, 1, GL_FALSE, MVstack.getCurrentMatrix());
						//glBindTexture(GL_TEXTURE_2D, uniqueTexture.getTexID());
						regSphere.render();
					MVstack.pop();
				}
				
				// MESH
				MVstack.push();
					MVstack.translate(mTest->getPosition());
					MVstack.multiply(mTest->getOrientation());
					glLineWidth(1.0);
					glUniformMatrix4fv(locationMV, 1, GL_FALSE, MVstack.getCurrentMatrix());
					//glBindTexture(GL_TEXTURE_2D, uniqueTexture.getTexID());
					mTest->render();
				MVstack.pop();

				// WAND
				MVstack.push();
					MVstack.translate(wand->getTrackerPosition());
					MVstack.multiply(wand->getTrackerRotation());
					
					glUniformMatrix4fv(locationMV, 1, GL_FALSE, MVstack.getCurrentMatrix());
					MVstack.push();
						MVstack.scale(wandRadius);
						glUniformMatrix4fv(locationMV, 1, GL_FALSE, MVstack.getCurrentMatrix());
						glBindTexture(GL_TEXTURE_2D, currentTexID);
						sphereWand.render();
						if (lines) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
					MVstack.pop();
						MVstack.push();
						translateVector[0] = -0.1f;
						translateVector[1] = 0.0f;
						translateVector[2] = 0.0f;
						MVstack.translate(translateVector);
						glUniformMatrix4fv(locationMV, 1, GL_FALSE, MVstack.getCurrentMatrix());
						glBindTexture(GL_TEXTURE_2D, currentTexID);
						boxWand.render();
					MVstack.pop();
				MVstack.pop();

			MVstack.pop();
		}

		// Back to the default framebuffer...
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		//Wand callback from VRPN
		wand->sendtoMainloop();

		//wand3d->start();

		// Do everything, distortion, front/back buffer swap...
		ovrHmd_EndFrame(hmd, g_EyePoses, g_EyeTextures);

		++l_FrameIndex;

		glfwPollEvents();

	}

	// Clean up FBO...
	glDeleteRenderbuffers(1, &l_DepthBufferId);
	glDeleteTextures(1, &l_TextureId);
	glDeleteFramebuffers(1, &l_FBOId);

	// Clean up Oculus...
	ovrHmd_Destroy(hmd);
	ovr_Shutdown();

	// Clean up window...
	glfwDestroyWindow(l_Window);
	glfwTerminate();

	return 1;
}

static void WindowSizeCallback(GLFWwindow* p_Window, int p_Width, int p_Height) {
	if (p_Width>0 && p_Height>0) {
		g_Cfg.OGL.Header.BackBufferSize.w = p_Width;
		g_Cfg.OGL.Header.BackBufferSize.h = p_Height;

		ovrBool l_ConfigureResult = ovrHmd_ConfigureRendering(hmd, &g_Cfg.Config, G_DISTORTIONCAPS, hmd->MaxEyeFov, g_EyeRenderDesc);
		if (!l_ConfigureResult) {
			printf("Configure failed.\n");
			exit(EXIT_FAILURE);
		}
	}
}

void GLRenderCallsOculus(){
	// Clear...
	//GL calls
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	//glDisable(GL_TEXTURE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glFrontFace(GL_CCW);
	if (L_MULTISAMPLING) {
		glEnable(GL_MULTISAMPLE);
	}
	else {
		glDisable(GL_MULTISAMPLE);
	}
}

void moveMesh(Device* wand, Mesh* mTest, bool buttonPressed, float* changePos, float* differenceR) {
	// Save first wand rotation transform in wandR
	float* wandR = wand->getTrackerRotation();
	float resultR[16];
	float resultPos[3];

	if (buttonPressed) {
		// Offset translation back to the original position of the mesh
		changePos[0] = mTest->getPosition()[0] - wand->getTrackerPosition()[0];
		changePos[1] = mTest->getPosition()[1] - wand->getTrackerPosition()[1];
		changePos[2] = mTest->getPosition()[2] - wand->getTrackerPosition()[2];

		// Get the difference betweeen the original mesh rotation transform and wandR  --   wandR * differenceR = meshR
		float* meshR = mTest->getOrientation();
		float invWandR[16] = { 0.0f };
		Utilities::invertMatrix(wandR, invWandR);
		Utilities::matrixMult(invWandR, meshR, differenceR);
	}

	// Resulting translation to be made on the mesh calculated from origin.
	resultPos[0] = wand->getTrackerPosition()[0] + changePos[0];
	resultPos[1] = wand->getTrackerPosition()[1] + changePos[1];
	resultPos[2] = wand->getTrackerPosition()[2] + changePos[2];

	// Resulting rotation to be made on the mesh
	Utilities::matrixMult(wandR, differenceR, resultR);

	mTest->setPosition(resultPos);
	mTest->setOrientation(resultR);
}

void print_GLM_matrix(glm::mat4 M) {
	double dArray[16] = { 0.0 };
	const float *pSource = (const float*)glm::value_ptr(M);
	for (int i = 0; i < 16; ++i){
		dArray[i] = pSource[i];
		cout << std::fixed << std::setprecision(2);
		cout << dArray[i] << "  ";
		if (i == 3 || i == 7 || i == 11)	cout << endl;
	}
	cout << endl << "---------------------" << endl;
}

void print_FLOAT_matrix(float* M) {
	for (int i = 0; i < 16; i++) {
		cout << std::fixed << std::setprecision(2);
		cout << M[i] << "  ";
		if (i == 3 || i == 7 || i == 11)	cout << endl;
	}
	cout << endl << "---------------------" << endl;
}