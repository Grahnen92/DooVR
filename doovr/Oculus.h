#include "Utilities.h"

//! Namespace that handles rendering to an Oculus Rift
namespace Oculus {

	//! Sets up a glfw window depending on the resolution of the Oculus Rift device
	static void WindowSizeCallback(GLFWwindow* p_Window, int p_Width, int p_Height);

	//! Handles tracking devices and objects in a scene. Renders to an Oculus Rift
	int runOvr();

}
