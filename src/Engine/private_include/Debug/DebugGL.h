#ifndef _ENGINE_DEBUG_GL_H_
#define _ENGINE_DEBUG_GL_H_

#include <Engine/Config.h>

#include <Engine/DevSupport/Logging.h>

#ifdef ENGINE_API_OPEN_GL

#include <GPU/OpenGL/OpenGL.h>
#include <GPU/OpenGL/Format.h>

namespace Engine
{
	/**
	 * Initializes OpenGL debugging.
	 */
	ENGINE_EXPORT void initGLDebug(const OpenGL::Format &fmt, GLDEBUGPROC callback, void* userparam);
}

#endif // ENGINE_API_OPEN_GL

#endif // _ENGINE_DEBUG_GL_H_