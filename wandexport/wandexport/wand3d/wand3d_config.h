#pragma once

#if defined(WIN32) && BUILD_SHARED_LIBS
#	ifdef Wand3d_EXPORTS
#		define WAND3D_DECLSPEC __declspec(dllexport)
#	else
#		define WAND3D_DECLSPEC __declspec(dllimport)
#	endif
#else
#	define WAND3D_DECLSPEC
#endif
