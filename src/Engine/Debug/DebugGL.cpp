#include "../private_include/Debug/DebugGL.h"

#ifdef ENGINE_API_OPEN_GL

#include <cassert>

#include <Engine/DevSupport/Logging.h>

namespace Engine
{
#ifdef ENGINE_DEVELOPMENT_SUPPORT
	void initGLDebug(const OpenGL::Format &fmt, GLDEBUGPROC callback, void* userparam)
	{
		assert( fmt.versionMajor >= 3 );

		if ( (fmt.versionMajor > 4) || (fmt.versionMajor == 4 && fmt.versionMinor >= 3) )
		{
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(callback, userparam);
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, true);
		}
		else if ( glewIsSupported("GL_ARB_debug_output") )
		{
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
			glDebugMessageCallbackARB(callback, userparam);
			glDebugMessageControlARB(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, true);
		}
		else
		{
			// Log(LogType::Warning, LogSource::Engine, LogSeverity::Medium, "OpenGL API debug output is not supported on this system.");
		}
	}
#else
	void initGLDebug(const OpenGL::Format &fmt, GLDEBUGPROC callback, void* userparam)
	{
	}
#endif // ENGINE_DEVELOPMENT_SUPPORT
}

#endif // ENGINE_API_OPEN_GL