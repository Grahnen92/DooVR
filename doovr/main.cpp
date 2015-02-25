#include <iostream>
#include "Utilities.h"
#include "Shader.h"
#include "MatrixStack.hpp"

#include <time.h>

using namespace std;

void setupViewport(GLFWwindow *window, GLfloat *P)
{
	int width, height;

	glfwGetWindowSize(window, &width, &height);

	P[0] = P[5] * height / width;

	glViewport(0, 0, width, height);
}

int main()
{
	
	GLfloat I[16] = { 1.0f, 0.0f, 0.0f, 0.0f
		, 0.0f, 1.0f, 0.0f, 0.0f
		, 0.0f, 0.0f, 1.0f, 0.0f
		, 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat P[16] = { 2.42f, 0.0f, 0.0f, 0.0f
		, 0.0f, 2.42f, 0.0f, 0.0f
		, 0.0f, 0.0f, -1.0f, -1.0f
		, 0.0f, 0.0f, -0.2f, 0.0f };

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

	Shader phongShader("vertexshader.glsl", "fragmentshader.glsl");

	//MatrixStack MVstack;
	//MVstack.init();

	while (!glfwWindowShouldClose(window)) {
		
		glfwPollEvents();

		//GL calls
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		(phongShader.programID);

		setupViewport(window, P);

		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}
