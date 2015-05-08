#include "twoDim.h"
#include "Wand.h"
#include "Vrpn.h"
#include "Shader.h"
#include "MatrixStack.h"
#include "Sphere.h"
#include "Plane.h"
#include "Cylinder.h"
// ---- Function dectarations ---- 
void modifyMesh(Mesh* mesh, GLFWwindow* w, Wand* wand);
void GLRenderCalls();
//! Sets up the GLFW viewport
void setupViewport(GLFWwindow *window, GLfloat *P);
// --------------------------------

// --- Global variables for testing ---
int global_i = 1;
int global_j = 0;
// ------------------------------------

int twoDim::run2D() {
	GLfloat I[16] = { 1.0f, 0.0f, 0.0f, 0.0f,
					  0.0f, 1.0f, 0.0f, 0.0f,
					  0.0f, 0.0f, 1.0f, 0.0f,
					  0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat P[16] = { 2.42f, 0.0f, 0.0f, 0.0f,
					  0.0f, 2.42f, 0.0f, 0.0f,
					  0.0f, 0.0f, -1.0f, -1.0f,
					  0.0f, 0.0f, -0.2f, 0.0f };
	GLint locationP;
	GLint locationMV;

	//GL INITIALIZATION ////////////////////////////////////////////////////////////////////////////////
	// start GLEW extension handler
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return 1;
	}

	//create GLFW window and select context
	GLFWwindow* window = glfwCreateWindow(640, 480, "hej", NULL, NULL);
	if (!window) {
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);

	//start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	// get version info
	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version as a string
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);

	// CREATE OBJECTS ////////////////////////////////////////////////////////////////////////////////
	Shader phongShader;
	phongShader.createShader("vertexshader.glsl", "fragmentshader.glsl");

	MatrixStack MVstack;
	MVstack.init();

	Mesh mTest;
	//Sphere sphere(glm::vec3(0.0f, 0.0f, 0.0f), 0.5f);
	Plane ground(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(100.0f, 100.0f));

	locationMV = glGetUniformLocation(phongShader.programID, "MV");
	locationP = glGetUniformLocation(phongShader.programID, "P");

	float translateVector[3] = { 0.0f, 0.0f, 0.0f };

	// Initilise VRPN connection
	Vrpn* mouse = new Vrpn(true, true, false, "Mouse");


	float test[3] = { 0.0f, 0.0f, 0.0f };
	//RENDER LOOP /////////////////////////////////////////////////////////////////////////////////////
	while (!glfwWindowShouldClose(window)) {

		//NECESSARY RENDER CALLS /////////////////////////////////////////////////////////////////////
		//modifyMesh(&mTest, window, mouse);
		glfwPollEvents();

		float wandRadius = 0.1;

		if (glfwGetKey(window, GLFW_KEY_G)){
			test[0] += 0.01f;
		}

		if (glfwGetKey(window, GLFW_KEY_O)) {

		//	mTest.updateVertexArray(test, true);
			//			deform.dilate(mTest.getVertexList(), mTest.getIndexList);
		}
		if (glfwGetKey(window, GLFW_KEY_P)) {
		//	mTest.updateVertexArray(test, false);
			//			deform.dilate(mTest.getVertexList(), mTest.getIndexList);
		}
		if (glfwGetKey(window, GLFW_KEY_N)) {

		//	mTest.moveThroughMesh((global_i + 1) * 20 + global_j);
			global_i = global_i + 2;
			global_j = global_j + 1;
		}

		GLRenderCalls();

		glUseProgram(phongShader.programID);

		setupViewport(window, P);
		glUniformMatrix4fv(locationP, 1, GL_FALSE, P);

		//SCENEGRAPH //////////////////////////////////////////////////////////////////////////////////
		//camera transforms 
		MVstack.push();
			translateVector[0] = 0.0f;
			translateVector[1] = -1.0f;
			translateVector[2] = -1.0f;
			MVstack.translate(translateVector);
			MVstack.rotAxis(glm::vec3(1.0f, 0.0f, 0.0f), -0.8f);
			//SCENE TRANSFORMS ////////////////////////////////////////////////////////////////////////////////////////////////////
			// ground render
			MVstack.push();
				translateVector[0] = 0.0f;
				translateVector[1] = -1.0f;
				translateVector[2] = 0.0f;
				MVstack.translate(translateVector);
				glUniformMatrix4fv(locationMV, 1, GL_FALSE, MVstack.getCurrentMatrix());

				//ground.render();
			MVstack.pop();

			//mesh render
			MVstack.push();
				translateVector[0] = 0.0f;
				translateVector[1] = -1.0f;
				translateVector[2] = -3.0f;
				MVstack.translate(translateVector);
				glUniformMatrix4fv(locationMV, 1, GL_FALSE, MVstack.getCurrentMatrix());

				mTest.render();
			MVstack.pop();
		MVstack.pop();

		mouse->sendtoMainloop();
		//mouse->getTrackerTransform();

		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}

void setupViewport(GLFWwindow *window, GLfloat *P) {
	int width, height;

	glfwGetWindowSize(window, &width, &height);

	P[0] = P[5] * height / width;

	glViewport(0, 0, width, height);
}

void GLRenderCalls() {
	//GL calls
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void modifyMesh(Mesh* mesh, GLFWwindow* window, Wand* wand) {
	glfwPollEvents();
	float test[3] = { 0.0f, 0.0f, 0.0f };
	float wandRadius = 0.1;

	if (glfwGetKey(window, GLFW_KEY_G)){
		test[0] += 0.1f;
	}

	if (glfwGetKey(window, GLFW_KEY_O)) {
//		mesh->updateVertexArray(test, true);
		//			deform.dilate(mTest.getVertexList(), mTest.getIndexList);
	}
	if (glfwGetKey(window, GLFW_KEY_P)) {
//		mesh->updateVertexArray(test, false);
		//			deform.dilate(mTest.getVertexList(), mTest.getIndexList);
	}
	if (glfwGetKey(window, GLFW_KEY_N)) {

//		mesh->moveThroughMesh((global_i + 1) * 20 + global_j);
		global_i = global_i + 2;
		global_j = global_j + 1;
	}
}
