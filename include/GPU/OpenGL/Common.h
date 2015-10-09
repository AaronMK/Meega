#ifndef _GPU_OPEN_GL_COMMON_H_
#define _GPU_OPEN_GL_COMMON_H_

#include "../Config.h"

#if defined(GPU_SUPPORT_OPEN_GL)
#	include "glew.h"
	GPU_DYNAMIC_FUNC_EXPORT GLEWContext* glewGetContext();

#	if defined(_WIN32)
#		include "Windows/wglew.h"
		GPU_DYNAMIC_FUNC_EXPORT WGLEWContext* wglewGetContext();

#		pragma comment(lib, "Opengl32.lib")
#		pragma comment(lib, "glu32.lib")
#	endif
#endif

#endif // _GPU_OPEN_GL_COMMON_H_