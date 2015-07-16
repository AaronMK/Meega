#ifndef _ENGINE_GPU_PIPELINE_H_
#define _ENGINE_GPU_PIPELINE_H_

#include <Engine/Config.h>

#include <Engine/Tasking/Fence.h>

#include <Concurrent/Producer.h>

#include <functional>

#include <Concurrent/FunctionTask.h>

#include <GPU/RenderTarget.h>

#ifdef ENGINE_API_OPEN_GL

#include <GPU/OpenGL/Context.h>

namespace Engine
{
	class GpuPipelinePlatform
	{
	public:
		OpenGL::Context* mWaitContext;
		OpenGL::Context* mRunContext;
	};
}
#else
#	error Unsupported platform for GpuPipeline
#endif

namespace Engine
{
	class GpuPipeline : public GpuPipelinePlatform
	{
		friend class Fence;
	public:
		GpuPipeline(GpuPipeline* shared = nullptr);
		virtual ~GpuPipeline();

		void enqueue(const std::function<void()> &func);
		void enqueue(std::function<void()>&& func);

		void setTarget(GPU::RenderTarget* target);
		void swapBuffers();

		void markForFlush();

		static GpuPipeline* current();

	private:
		bool flush;

		Concurrent::Producer<Fence*> mFenceQueue;
		Concurrent::Producer<std::function<void()>> mTaskQueue;

		Concurrent::FunctionTask mWaitTask;
		Concurrent::FunctionTask mRunTask;

		void waitThread();
		void runThread();
	};
}

#endif // _ENGINE_GPU_PIPELINE_H_