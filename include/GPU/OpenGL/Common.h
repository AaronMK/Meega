#ifndef _GPU_OPEN_GL_COMMON_H_
#define _GPU_OPEN_GL_COMMON_H_

#include "../Config.h"

#if defined(GPU_SUPPORT_OPEN_GL)
#	include "glew.h"

#	if defined(_WIN32)
#		include "Windows/wglew.h"

#		pragma comment(lib, "Opengl32.lib")
#		pragma comment(lib, "glu32.lib")
#	endif
#endif

#endif // _GPU_OPEN_GL_COMMON_H_