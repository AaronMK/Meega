#ifndef _ENGINE_FENCE_INTERNAL_H_
#define _ENGINE_FENCE_INTERNAL_H_

#include "../../Config.h"

#ifdef ENGINE_API_OPEN_GL

#include <Concurrent/Condition.h>
#include <GPU/OpenGL/OpenGL.h>

namespace Engine
{
	/**
	 * @internal
	 */
	class ENGINE_EXPORT FenceInternal
	{
	public:
		Concurrent::Condition done;
		GLsync mApiFence;
	};
}

#else
#	Fence not supported on current platform.
#endif

#endif // _ENGINE_FENCE_INTERNAL_H_