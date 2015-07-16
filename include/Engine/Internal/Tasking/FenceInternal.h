#ifndef _ENGINE_FENCE_INTERNAL_H_
#define _ENGINE_FENCE_INTERNAL_H_

#include <Engine/Config.h>

#ifdef ENGINE_API_OPEN_GL

#include <GPU/OpenGL/OpenGL.h>

namespace Engine
{
	class ENGINE_DYNAMIC_CLASS FenceInternal
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