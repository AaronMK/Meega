#include <Engine/Tasking/Pipeline.h>

#include <Concurrent/Task.h>

#include "../private_include/Tasking/GpuPipeline.h"

using namespace Concurrent;

namespace Engine
{
	GpuPipeline* pipeRender = nullptr;
	GpuPipeline* pipeLoad = nullptr;

	bool initPipeline()
	{
		assert(nullptr == pipeRender && nullptr == pipeLoad);

		pipeRender = new GpuPipeline;
		pipeLoad = new GpuPipeline(pipeRender);

		return true;
	}

	extern GpuPipeline* currentPipeline()
	{
		Task* currentTask = Task::current();

		if (currentTask == pipeRender || currentTask == pipeLoad)
			return dynamic_cast<GpuPipeline*>(currentTask);

		return nullptr;
	}

	void shutdownPipeline()
	{
		delete pipeRender;
		pipeRender = nullptr;

		delete pipeLoad;
		pipeLoad = nullptr;
	}

	namespace Render
	{
		void enqueue(std::function<void()>&& function)
		{
			assert(nullptr != pipeRender);
			pipeRender->enqueue(std::forward<std::function<void()>>(function));
		}

		void setTarget(GPU::RenderTarget* target)
		{
			pipeRender->setTarget(target);
		}
		
		void swapBuffers()
		{
			pipeRender->swapBuffers();
		}

		void clearTarget()
		{
			pipeRender->setTarget(nullptr);
		}

		void clear(unsigned int buffers)
		{
			glClear(buffers);
		}

		void flush()
		{
			pipeRender->markForFlush();
		}

		bool inPipeline()
		{
			return pipeRender->inPipeline();
		}
	}

	namespace Load
	{
		void enqueue(std::function<void()>&& function)
		{
			assert(nullptr != pipeLoad);
			pipeLoad->enqueue(std::forward<std::function<void()>>(function));
		}

		void flush()
		{
			assert(nullptr != pipeLoad);
			if (pipeLoad->inPipeline())
			{
				Fence fence;
				Load::enqueue([&]()
				{
					fence.activate();
					glFlush();
				});
				fence.wait();
			}
		}

		bool inPipeline()
		{
			assert(nullptr != pipeLoad);
			return (pipeLoad->inPipeline());
		}
	}
}