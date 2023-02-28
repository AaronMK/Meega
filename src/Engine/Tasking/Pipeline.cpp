#include <Engine/Tasking/Pipeline.h>

#include <StdExt/Concurrent/Task.h>

#include "../private_include/Tasking/GpuPipeline.h"

using namespace StdExt::Concurrent;

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
		void enqueue(std::function<void()>&& function)
		{
			assert(nullptr != pipeRender);
			pipeRender->enqueue(std::forward<std::function<void()>>(function));
		}

		void setTarget(GPU::RenderTarget* target)
		{
			pipeRender->setTarget(target);
		}
		
		void viewport(int left, int bottom, int width, int height)
		{
			glViewport(left, bottom, width, height);
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
			Fence fence;
			Load::enqueue([&]()
			{
				fence.activate(pipeLoad);
				glFlush();
			});
			fence.wait();
		}
	}
}