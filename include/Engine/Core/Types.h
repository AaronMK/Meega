#ifndef _ENGINE_TYPES_H_
#define _ENGINE_TYPES_H_

#include <Engine/Config.h>

#ifdef ENGINE_API_OPEN_GL

#include <GPU/OpenGL/Common.h>

namespace Engine
{
	typedef GLubyte apiUByte;

	typedef float  float32_t;
	typedef double float64_t;
}

#endif ENGINE_API_OPEN_GL;

#endif // _ENGINE_TYPES_H_