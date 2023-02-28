#ifndef _ENGINE_FENCE_H_
#define _ENGINE_FENCE_H_

#include "../Config.h"
#include "../Internal/Tasking/FenceInternal.h"

#include <StdExt/Concurrent/Condition.h>

namespace Engine
{
	class ENGINE_EXPORT Fence : public FenceInternal
	{
		friend class GpuPipeline;
	public:
		Fence();
		virtual ~Fence();

		void activate(GpuPipeline* pipeline);
		void wait();
	};
}

#endif // _ENGINE_FENCE_H_