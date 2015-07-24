#include <Engine/Tasking/Pipeline.h>

#include <Concurrent/Task.h>

#include "../private_include/Tasking/GpuPipeline.h"

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

	void shutdownPipeline()
	{
		delete pipeRender;
		pipeRender = nullptr;

		delete pipeLoad;
		pipeLoad = nullptr;
	}

	namespace Render
	{
		void enqueue(const std::function<void()> &function)
		{
			enqueue(std::function<void()>(function));
		}

		void enqueue(std::function<void()>&& function)
		{
			assert(nullptr != pipeRender);
			pipeRender->enqueue(std::move(function));
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
		void enqueue(const std::function<void()> &function)
		{
			enqueue(std::function<void()>(function));
		}

		void enqueue(std::function<void()>&& function)
		{
			assert(nullptr != pipeLoad);
			pipeLoad->enqueue(std::move(function));
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