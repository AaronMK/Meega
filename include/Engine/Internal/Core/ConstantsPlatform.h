#ifndef _CONSTANTS_PLATFORM_H_
#define _CONSTANTS_PLATFORM_H_

#include "../../Config.h"

#ifdef ENGINE_API_OPEN_GL

#include <GPU/OpenGL/Common.h>

namespace Engine
{
	constexpr unsigned int COLOR_BUFFER_BIT_v        = GL_COLOR_BUFFER_BIT;
	constexpr unsigned int DEPTH_BUFFER_BIT_v        = GL_DEPTH_BUFFER_BIT;
	constexpr unsigned int STENCIL_BUFFER_BIT_v      = GL_STENCIL_BUFFER_BIT;
}
#else
#endif

#endif // _CONSTANTS_PLATFORM_H_