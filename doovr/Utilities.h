//! Namespace that handles necassary includes and various functions

#include "GL/glew.h"

#include <Windows.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL

#ifdef __APPLE__
#define GLFW_EXPOSE_NATIVE_COCOA
#define GLFW_EXPOSE_NATIVE_NSGL
#endif
#include "GLFW/glfw3.h"
#include <GLFW/glfw3native.h>

#include "glm/glm.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/transform.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/gtx/string_cast.hpp"

#include "Device.h"

#include <OVR/OVR.h>
#include <Src/OVR_CAPI.h>
#include <Src/OVR_CAPI_GL.h>
#include <iomanip>      // std::setprecision

namespace Utilities {
	
	double displayFPS(GLFWwindow* window);
	
}