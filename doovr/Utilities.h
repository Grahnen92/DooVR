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
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <OVR/OVR.h>
#include <OVR_CAPI.h>
#include <OVR_CAPI_GL.h>

namespace Utilities {

}