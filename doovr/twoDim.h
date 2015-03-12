
#include "Utilities.h"

#include <time.h>

//! Namespace that handles rendering to a 2D display

namespace twoDim{
	//! Sets up the GLFW viewport
	void setupViewport(GLFWwindow *window, GLfloat *P);

	//! Handles tracking devices and objects in a scene. Renders to a 2D display
	int run2D();

}