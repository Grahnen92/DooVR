 /* 
   	DooVR, Modelling application using Oculus Rift and Sixense STEM.
    Copyright (C) 2015  Isabelle Forsman, Olle Grahn, Jonathan Bosson, Johan Nordin.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

	isafo268@student.liu.se, ollgr444@student.liu.se, jonbo665@student.liu.se, johno855@student.liu.se,
*/

#include <iostream>
#include "Utilities.h"
#include "Shader.h"
#include "MatrixStack.hpp"
#include "Entity.h"
#include "Sphere.h"
#include "Plane.h"
#include "Vrpn.h"



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

	GLint locationP;
	GLint locationMV;
	// start GLEW extension handler
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return 1;
	}

#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

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

	Shader phongShader;
	phongShader.createShader("vertexshader.glsl", "fragmentshader.glsl");

	MatrixStack MVstack;
	MVstack.init();

	Sphere test(glm::vec3(0.0f, 0.0f, 0.0f), 2.0f, 0.5f);
	Plane ground(glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, glm::vec2(10.0f, 10.0f));

	locationMV = glGetUniformLocation(phongShader.programID, "MV");
	locationP = glGetUniformLocation(phongShader.programID, "P");

	Vrpn* con = new Vrpn();
	con->connectDevices();

	while (!glfwWindowShouldClose(window)) {
		
		glfwPollEvents();

		//GL calls
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glUseProgram(phongShader.programID);

		glUniformMatrix4fv(locationP, 1, GL_FALSE, P);
		setupViewport(window, P);

		MVstack.push();
			MVstack.translate(glm::vec3(0.0f, 0.0f, -5.0f));
			glUniformMatrix4fv(locationMV, 1, GL_FALSE, MVstack.getCurrentMatrix());

			test.render();
		MVstack.pop();
		MVstack.push();
			MVstack.translate(glm::vec3(0.0f, -1.0f, -5.0f));
			MVstack.rotX(5.0f);
			glUniformMatrix4fv(locationMV, 1, GL_FALSE, MVstack.getCurrentMatrix());
			ground.render();
		MVstack.pop();

		con->sendtoMainloop();

		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}
