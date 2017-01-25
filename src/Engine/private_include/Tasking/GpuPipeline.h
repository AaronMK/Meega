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

#else
#	error Unsupported platform for GpuPipeline
#endif

namespace Engine
{
	class GpuPipeline : public Concurrent::Task
	{
		friend class Fence;
	public:
		GpuPipeline(GpuPipeline* shared = nullptr);
		virtual ~GpuPipeline();

		virtual void run();

		void enqueue(std::function<void()>&& func);

		void setTarget(GPU::RenderTarget* target);
		void swapBuffers();

		void markForFlush();

		bool inPipeline() const;

	private:
#ifdef ENGINE_API_OPEN_GL
		OpenGL::Context* mWaitContext;
		OpenGL::Context* mRunContext;
#endif // ENGINE_API_OPEN_GL

		bool flush;

		Concurrent::Producer<Fence*> mFenceQueue;
		Concurrent::Producer<std::function<void()>> mTaskQueue;
	};
}

#endif // _ENGINE_GPU_PIPELINE_H_