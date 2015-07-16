#ifndef _ENGINE_FENCE_H_
#define _ENGINE_FENCE_H_

#include <Engine/Config.h>

#include <Concurrent/Condition.h>

#include <Engine/Internal/Tasking/FenceInternal.h>

namespace Engine
{
	class ENGINE_DYNAMIC_CLASS Fence : public FenceInternal
	{
		friend class GpuPipeline;
	public:
		Fence();
		virtual ~Fence();

		void activate();
		void wait();
	};
}

#endif // _ENGINE_FENCE_H_