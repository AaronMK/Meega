#ifndef _ENGINE_PROGRAM_PLATFORM_H_
#define _ENGINE_PROGRAM_PLATFORM_H_

#include "../../Config.h"

#ifdef ENGINE_API_OPEN_GL

#include <GPU/OpenGL/Common.h>

namespace Engine
{
	class ENGINE_EXPORT ProgramPlatform
	{
	public:
		GLuint  mProgramID;

	protected:
		static void move(ProgramPlatform* src, ProgramPlatform* dst);
	};
}
#else
#	error Program is not supported on the current platform.
#endif

#endif // _ENGINE_PROGRAM_PLATFORM_H_