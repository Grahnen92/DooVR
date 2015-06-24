#pragma once

#include <iostream>
#include <fstream>

#include "configure.h"
#include "MatrixStack.h"
#include "Sphere.h"
#include "Plane.h"
#include "Texture.h"
#include "Shader.h"
#include "hexBox.h"
#include "Box.h"
#include "Wand.h"
#include "Vrpn.h"

//#define GLFW_EXPOSE_NATIVE_WIN32
//#define GLFW_EXPOSE_NATIVE_WGL

using namespace std;

// ------- Function declerations --------
//! Sets up a glfw window depending on the resolution of the Oculus Rift device
static void WindowSizeCallbackConf(GLFWwindow *p_Window, int p_Width, int p_Height);
// function containing all nessesary OpenGL render calls
void GLRenderCallsOculusConf();
//! Saves the calibration to a ini file
void saveCalibration(float* transform, float& eyeHeight, const char* fileName);

// --- Variable Declerations ------------
const bool L_MULTISAMPLING = false;
const int G_DISTORTIONCAPS = 0
| ovrDistortionCap_Vignette
| ovrDistortionCap_Chromatic
| ovrDistortionCap_Overdrive
//| ovrDistortionCap_TimeWarp // Turning this on gives ghosting???
;

ovrHmd hmd_conf;
ovrGLConfig g_Cfg_conf;
ovrEyeRenderDesc g_EyeRenderDesc_conf[2];


const float EYEHEIGHT{ OVR_DEFAULT_EYE_HEIGHT };
// --------------------------------------

bool configure::coRegister() {

	ovrVector3f g_EyeOffsets[2];
	ovrPosef g_EyePoses[2];
	ovrTexture g_EyeTextures[2];
	OVR::Matrix4f g_ProjectionMatrix[2];
	OVR::Sizei g_RenderTargetSize;
	ovrVector3f g_CameraPosition;

	GLfloat I[16] = { 1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f };

	GLfloat P[16] = { 2.42f, 0.0f, 0.0f, 0.0f,
		0.0f, 2.42f, 0.0f, 0.0f,
		0.0f, 0.0f, -1.0f, -1.0f,
		0.0f, 0.0f, -0.2f, 0.0f };

	// Lightposition 
	float lPos[4] = { 2.0f, 2.0f, 2.0f, 1.0f };
	float lPos2[4] = { -2.0f, 2.0f, 2.0f, 1.0f };
	float lPosTemp[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float LP[4];
	float* pmat4;
	float mat4[16];

	// Save old positions and transforms
	float changePos[3] = { 0.0f };
	float differenceR[16] = { 0.0f };
	float lastPos[3] = { 0.0f, 0.0f, 0.0f };
	float currPos[3] = { 0.0f, 0.0f, 0.0f };

	// Configuration variables
	int regCounter = 0;
	int n = 0;
	int resetCounter = 0;

	float regSpherePos[16] = { 0.0f, 0.0f, 0.4f, 0.4f,		// Sp1 0.2
							   0.0f, -0.4f, 0.0f, -0.4f,	// Sp2 0.5
							   0.8f, 1.0f, 1.0f, 0.8f,		// Sp3 0.45
							   1.0f, 1.0f, 1.0f, 1.0f };	// Sp4

	float pos[16] = { 0.0f };
	float transform[16] = { 0.0f };
	float invPos[16] = { 0.0f };
	float eyeHeight = OVR_DEFAULT_EYE_HEIGHT;
	float MAX_HEX_HEIGHT = -eyeHeight + 0.95f;
	float MIN_HEX_HEIGHT = -eyeHeight + 0.9f;
	float eye, floor;

	// FPS
	double fps = 0;

	// Translation vector -- used for tranlate objects in SceneGraph
	float translateVector[3] = { 0.0f, 0.0f, 0.0f };

	// Size of the wand tool
	float wandRadius = 0.05f;

	// States
	bool buttonPressed = false;
	bool buttonHeld = false;
	bool buttonReleased = false;
	bool lines = false;

	// Location used for UNIFORMS in shader
	GLint locationLP;
	GLint locationP;
	GLint locationMV;
	GLint locationTex;

	GLint locationMeshMV;
	//GLint locationMeshLP[nLightsources + 1];
	GLint locationMeshP;
	GLint locationMeshLP;
	GLint locationMeshLP2;
	GLint locationMeshLP3;
	GLint locationMeshLP4;

	GLint locationWandMV;
	GLint locationWandP;

	//INITIALIZE OVR /////////////////////////////////////////////////////
	ovr_Initialize();
	int det;
	// Check for attached head mounted display...
	hmd_conf = ovrHmd_Create(0);
	if (!hmd_conf) {
		printf("No Oculus Rift device attached, using virtual version...\n");
		hmd_conf = ovrHmd_CreateDebug(ovrHmd_DK2);

		det = ovrHmd_Detect();
		cout << det << endl;
	}

	// Check to see if we are running in "Direct" or "Extended Desktop" mode...
	bool l_DirectMode = ((hmd_conf->HmdCaps & ovrHmdCap_ExtendDesktop) == 0);

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

		l_ClientSize.w = hmd_conf->Resolution.w; // Something reasonable, smaller, but maintain aspect ratio...
		l_ClientSize.h = hmd_conf->Resolution.h; // Something reasonable, smaller, but maintain aspect ratio...
	}
	else {// Extended Desktop mode...
		printf("Running in \"Extended Desktop\" mode...\n");
		int l_Count;
		GLFWmonitor** l_Monitors = glfwGetMonitors(&l_Count);
		switch (l_Count) {
		case 0: {
			printf("No monitors found, exiting...\n");
			exit(EXIT_FAILURE);
			break;
		} case 1: {
			printf("Two monitors expected, found only one, using primary...\n");
			l_Monitor = glfwGetPrimaryMonitor();
			break;
		} case 2: {
			printf("Two monitors found, using second monitor...\n");
			l_Monitor = l_Monitors[1];
			break;
		} default: {
			printf("More than two monitors found, using second monitor...\n");
			l_Monitor = l_Monitors[1];
		}
		}

		l_ClientSize.w = hmd_conf->Resolution.w; // 1920 for DK2...
		l_ClientSize.h = hmd_conf->Resolution.h; // 1080 for DK2...
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
		ovrBool l_AttachResult = ovrHmd_AttachToWindow(hmd_conf, glfwGetWin32Window(l_Window), NULL, NULL);
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

	l_EyeTextureSizes[ovrEye_Left] = ovrHmd_GetFovTextureSize(hmd_conf, ovrEye_Left, hmd_conf->MaxEyeFov[ovrEye_Left], 1.0f);
	l_EyeTextureSizes[ovrEye_Right] = ovrHmd_GetFovTextureSize(hmd_conf, ovrEye_Right, hmd_conf->MaxEyeFov[ovrEye_Right], 1.0f);

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
	g_Cfg_conf.OGL.Header.API = ovrRenderAPI_OpenGL;
	g_Cfg_conf.OGL.Header.BackBufferSize.w = l_ClientSize.w;
	g_Cfg_conf.OGL.Header.BackBufferSize.h = l_ClientSize.h;
	g_Cfg_conf.OGL.Header.Multisample = (L_MULTISAMPLING ? 1 : 0);

	g_Cfg_conf.OGL.Window = glfwGetWin32Window(l_Window);
	g_Cfg_conf.OGL.DC = GetDC(g_Cfg_conf.OGL.Window);

	// Enable capabilities...
	// ovrHmd_SetEnabledCaps(hmd, ovrHmdCap_LowPersistence | ovrHmdCap_DynamicPrediction);

	ovrBool l_ConfigureResult = ovrHmd_ConfigureRendering(hmd_conf, &g_Cfg_conf.Config, G_DISTORTIONCAPS, hmd_conf->MaxEyeFov, g_EyeRenderDesc_conf);
	if (!l_ConfigureResult) {
		printf("Configure failed.\n");
		exit(EXIT_FAILURE);
	}

	// Start the sensor which provides the Rift�s pose and motion...
	uint32_t l_SupportedSensorCaps = ovrTrackingCap_Orientation | ovrTrackingCap_MagYawCorrection | ovrTrackingCap_Position;
	uint32_t l_RequiredTrackingCaps = 0;
	ovrBool l_TrackingResult = ovrHmd_ConfigureTracking(hmd_conf, l_SupportedSensorCaps, l_RequiredTrackingCaps);
	if (!l_TrackingResult) {
		printf("Could not start tracking...");
		exit(EXIT_FAILURE);
	}

	// set projection matrix for each eye
	g_ProjectionMatrix[ovrEye_Left] = ovrMatrix4f_Projection(g_EyeRenderDesc_conf[ovrEye_Left].Fov, 0.3f, 100.0f, true);
	g_ProjectionMatrix[ovrEye_Right] = ovrMatrix4f_Projection(g_EyeRenderDesc_conf[ovrEye_Right].Fov, 0.3f, 100.0f, true);

	// set IPD offset values
	g_EyeOffsets[ovrEye_Left] = g_EyeRenderDesc_conf[ovrEye_Left].HmdToEyeViewOffset;
	g_EyeOffsets[ovrEye_Right] = g_EyeRenderDesc_conf[ovrEye_Right].HmdToEyeViewOffset;

	//glfwSetKeyCallback(l_Window, KeyCallback);
	glfwSetWindowSizeCallback(l_Window, WindowSizeCallbackConf);

	//DECLARE AND CREATE SHADERS ///////////////////////////////////////////////////////////////////////////////////
	Shader phongShader;
	phongShader.createShader("vertexshader.glsl", "fragmentshader.glsl");
	Shader meshShader;
	meshShader.createShader("vshader.glsl", "fshader.glsl");
	Shader sphereShader;
	sphereShader.createShader("vShaderWand.glsl", "fShaderWand.glsl");

	// CREATE MATRIX STACK
	MatrixStack MVstack;
	MVstack.init();

	//DECLARE SCENE OBJECTS ///////////////////////////////////////////////////////////////////////////////////
	Sphere regSphere(0.0f, 0.0f, 0.0f, 0.05f);							// Sphere used for co-registration.

	Plane ground(0.0f, 0.0f, 0.0f, 100.0f, 100.0f);			//Ground plane
	Box boxPoint(0.0f, 0.0f, 0.0f, 0.005f, 0.005f, 0.005f);	//box in the middle of the wand
	hexBox refBox(0.0f, -eyeHeight + 1.5f, -2.0f, 0, 0);	//hexBox representing the Oculus camera

	// Wand = Box + sphere
	Box boxWand(0.0f, 0.0f, 0.0f, 0.20f, 0.03f, 0.03f);
	Sphere sphereWand(0.0f, 0.0f, 0.0f, 1.0f);

	// Initilise VRPN connection with the Intersense wand
	//Device* wand = new Device(true, true, false, "Mouse");
	Vrpn* wand = new Vrpn(true, true, true, "Wand");

	// TEXTURES ///////////////////////////////////////////////////////////////////////////////////////////////
	glEnable(GL_TEXTURE_2D);
	// Wand function textures
	Texture move("../Textures/move.DDS");
	Texture dilate("../Textures/up.DDS");
	Texture erode("../Textures/down.DDS");
	Texture dnp("../Textures/push.DDS");

	// Scene textures
	Texture groundTex("../Textures/floor3.DDS");
	Texture coregister("../Textures/coregister3.DDS");
	Texture hexTex("../Textures/panel3.DDS");

	GLuint currentTexID = move.getTextureID();

	//UNIFORM VARIABLES WITH SHADER ///////////////////////////////////////////////////////////////////////////
	locationMV = glGetUniformLocation(phongShader.programID, "MV");						// ModelView Matrix
	locationP = glGetUniformLocation(phongShader.programID, "P");						// Perspective Matrix
	locationLP = glGetUniformLocation(phongShader.programID, "lightPos");			// Light position
	locationTex = glGetUniformLocation(phongShader.programID, "tex");					// Texture Matrix

	locationWandMV = glGetUniformLocation(sphereShader.programID, "MV");					// ModelView Matrix
	locationWandP = glGetUniformLocation(sphereShader.programID, "P");					// Perspective Matrix

	//ovrHmd_RecenterPose(hmd);
	ovrHmd_DismissHSWDisplay(hmd_conf); // dismiss health safety warning

	//wand->setTransformMatrix(I) ; /////////////////////////////////////////////////////

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

		// CALIBRATION /////////////////////////////////////////////////////////////////////////////////////
		if (buttonPressed && wand->getButtonNumber() == 5) { // check if the trigger is pressed
			
			cout << regCounter << endl;
			// the first 4 clicks are to calibrate the wand
			if (regCounter <= 3) {
				for (int i = 0; i < 3; i++) { // Save wand position & rotation
					pos[i * 4 + regCounter] = wand->getWandPosition()[i];
				}
				pos[12 + regCounter] = 1.0f;
			}
			// set the wand transform after calibration is done
			if (regCounter == 3) {
				// (M1, M2, Mout) -> Mout = M2 * M1
				linAlg::invertMatrix(pos, invPos);
				linAlg::matrixMult(invPos, regSpherePos, transform);
				wand->setWandTransform(transform);
			}
			// fourth sets eye height
			else if (regCounter == 4) {
				eye = wand->getWandPosition()[1];
			}
			// fifth sets Floor position
			else if (regCounter == 5) {
				floor = wand->getWandPosition()[1];
			}

			regCounter++;
			// set the eye height
			if (regCounter == 6) {
				const char* userName;

				//eyeHeight = ovrHmd_GetFloat(hmd_conf, OVR_KEY_PLAYER_HEIGHT, 1.7) + eye;

				eyeHeight = eye - floor;
				MAX_HEX_HEIGHT = -eyeHeight + 0.95f;
				MIN_HEX_HEIGHT = -eyeHeight + 0.9f;

				// save configfile as Oculus profile name, if profile name doesn't exist save as: wandCalibration
				userName = ovrHmd_GetString(hmd_conf, OVR_KEY_USER, "wandCalibration");
				saveCalibration(transform, eyeHeight, userName);
				regCounter = 0;
			}
		}

		else if (buttonPressed && wand->getButtonNumber() != 5) {
			glfwSetWindowShouldClose(l_Window, GL_TRUE);
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////////
		// Save position of tracker from last frame to get deltaPos
		lastPos[0] = wand->getWandPosition()[0];
		lastPos[1] = wand->getWandPosition()[1];
		lastPos[2] = wand->getWandPosition()[2];

		// Begin the frame...
		ovrHmd_BeginFrame(hmd_conf, l_FrameIndex);

		// Get eye poses for both the left and the right eye. g_EyePoses contains all Rift information: orientation, positional tracking and
		// the IPD in the form of the input variable g_EyeOffsets.
		ovrHmd_GetEyePoses(hmd_conf, l_FrameIndex, g_EyeOffsets, g_EyePoses, NULL);

		// Bind the FBO...
		glBindFramebuffer(GL_FRAMEBUFFER, l_FBOId);

		GLRenderCallsOculusConf();


		for (int l_EyeIndex = 0; l_EyeIndex<ovrEye_Count; l_EyeIndex++) {

			//OCULUS/CAMERA TRANSFORMS ------------------------------------------------------------------------------
			MVstack.push();
				ovrEyeType l_Eye = hmd_conf->EyeRenderOrder[l_EyeIndex];

				glViewport(g_EyeTextures[l_Eye].Header.RenderViewport.Pos.x,
					g_EyeTextures[l_Eye].Header.RenderViewport.Pos.y,
					g_EyeTextures[l_Eye].Header.RenderViewport.Size.w,
					g_EyeTextures[l_Eye].Header.RenderViewport.Size.h);

				glUseProgram(phongShader.programID);
				// Pass projection matrix on to OpenGL...
				glUniformMatrix4fv(locationP, 1, GL_FALSE, &(g_ProjectionMatrix[l_Eye].Transposed().M[0][0]));
				glUniform1i(locationTex, 0);

				// Multiply with orientation retrieved from sensor...
				OVR::Quatf l_Orientation = OVR::Quatf(g_EyePoses[l_Eye].Orientation);
				OVR::Matrix4f l_ModelViewMatrix = OVR::Matrix4f(l_Orientation.Inverted());
				MVstack.multiply(&(l_ModelViewMatrix.Transposed().M[0][0]));


				//!-- Translation due to positional tracking (DK2) and IPD...
				float eyePoses[3] = { -g_EyePoses[l_Eye].Position.x, -g_EyePoses[l_Eye].Position.y, -g_EyePoses[l_Eye].Position.z };
				MVstack.translate(eyePoses);

				//POSSABLY DOABLE IN SHADER
				pmat4 = MVstack.getCurrentMatrix();
				for (int i = 0; i < 16; i++)
					mat4[i] = pmat4[i];

				linAlg::transpose(mat4);
				linAlg::vectorMatrixMult(mat4, lPos, LP);
				linAlg::vectorMatrixMult(mat4, lPos2, lPosTemp);
				glUniformMatrix4fv(locationMV, 1, GL_FALSE, MVstack.getCurrentMatrix());

				//SCENEOBJECT TRANSFORMS----------------------------------------------------------------
				MVstack.push();
					// RENDER GROUND ---------------------------------------------------------------------
					MVstack.push();
						translateVector[0] = 0.0f;
						translateVector[1] = -eyeHeight;
						translateVector[2] = 0.0f;
						MVstack.translate(translateVector);
						glUniformMatrix4fv(locationMV, 1, GL_FALSE, MVstack.getCurrentMatrix());
						glUniform4fv(locationLP, 1, LP);
						glBindTexture(GL_TEXTURE_2D, groundTex.getTextureID());
						ground.render();
					MVstack.pop();
					glBindTexture(GL_TEXTURE_2D, 0);
					//RENDER WAND---------------------------------------------------------------------------
					MVstack.push();
						MVstack.translate(wand->getWandPosition());
						MVstack.multiply(wand->getWandOrientation());

						glUniformMatrix4fv(locationMV, 1, GL_FALSE, MVstack.getCurrentMatrix());
						boxPoint.render();

						MVstack.push();
							translateVector[0] = -0.1f;
							translateVector[1] = 0.0f;
							translateVector[2] = 0.0f;
							MVstack.translate(translateVector);
							glUniformMatrix4fv(locationMV, 1, GL_FALSE, MVstack.getCurrentMatrix());
							glBindTexture(GL_TEXTURE_2D, hexTex.getTextureID());
							boxWand.render();
						MVstack.pop();
						MVstack.push();
							MVstack.scale(wandRadius);
							glUseProgram(sphereShader.programID);
							glUniformMatrix4fv(locationWandP, 1, GL_FALSE, &(g_ProjectionMatrix[l_Eye].Transposed().M[0][0]));
							glUniformMatrix4fv(locationWandMV, 1, GL_FALSE, MVstack.getCurrentMatrix());
							sphereWand.render();
						MVstack.pop();
					MVstack.pop();

					glUseProgram(phongShader.programID);
				MVstack.pop();

				// render Coregistration spheres
				if (regCounter <= 3) {
					MVstack.push();
					translateVector[0] = regSpherePos[0 + regCounter];
					translateVector[1] = regSpherePos[4 + regCounter];
					translateVector[2] = regSpherePos[8 + regCounter];
					MVstack.translate(translateVector);
					glUniformMatrix4fv(locationMV, 1, GL_FALSE, MVstack.getCurrentMatrix());
					glBindTexture(GL_TEXTURE_2D, coregister.getTextureID());
					regSphere.render();
					MVstack.pop();
				}
			MVstack.pop();
		}

		// Back to the default framebuffer...
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		//Wand callback from VRPN
		wand->sendtoMainloop();

		// Do everything, distortion, front/back buffer swap...
		ovrHmd_EndFrame(hmd_conf, g_EyePoses, g_EyeTextures);
		++l_FrameIndex;
		glfwPollEvents();
	}

	// Clean up FBO...
	glDeleteRenderbuffers(1, &l_DepthBufferId);
	glDeleteTextures(1, &l_TextureId);
	glDeleteFramebuffers(1, &l_FBOId);

	// Clean up Oculus...
	ovrHmd_Destroy(hmd_conf);
	ovr_Shutdown();

	// Clean up window...
	glfwDestroyWindow(l_Window);
	glfwTerminate();

	return 0;
}

static void WindowSizeCallbackConf(GLFWwindow* p_Window, int p_Width, int p_Height) {
	if (p_Width>0 && p_Height>0) {
		g_Cfg_conf.OGL.Header.BackBufferSize.w = p_Width;
		g_Cfg_conf.OGL.Header.BackBufferSize.h = p_Height;

		ovrBool l_ConfigureResult = ovrHmd_ConfigureRendering(hmd_conf, &g_Cfg_conf.Config, G_DISTORTIONCAPS, hmd_conf->MaxEyeFov, g_EyeRenderDesc_conf);
		if (!l_ConfigureResult) {
			printf("Configure failed.\n");
			exit(EXIT_FAILURE);
		}
	}
}

void GLRenderCallsOculusConf(){
	// Clear...
	//GL calls
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	//glDisable(GL_TEXTURE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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

void saveCalibration(float* transform, float& eyeHeight, const char* profileName){

	string fileName(profileName);

	ofstream wandCal;
	wandCal.open(fileName + ".ini");
	for (int i = 0; i < 16; i++) {
		wandCal << transform[i] << endl;
	}

	wandCal << eyeHeight;
	wandCal.close();
}