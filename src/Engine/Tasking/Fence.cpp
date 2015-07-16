#include <Engine/Tasking/Fence.h>

#include "../private_include/Tasking/GpuPipeline.h"

#include <cassert>

namespace Engine
{
	Fence::Fence()
	{
		mApiFence = 0;
	}

	Fence::~Fence()
	{
		assert(0 == mApiFence);
	}

	void Fence::activate()
	{
		GpuPipeline* pipeline = GpuPipeline::current();
		assert(nullptr != pipeline && 0 == mApiFence && false == done.isTriggered());
		
		mApiFence = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
		pipeline->mFenceQueue.push(this);
	}

	void Fence::wait()
	{
		done.wait();
		done.reset();
	}
}