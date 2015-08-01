#ifndef _ENGINE_PIPELINE_H_
#define _ENGINE_PIPELINE_H_

#include <Engine/Tasking/Fence.h>
#include <Engine/Core/Constants.h>

#include <GPU/RenderTarget.h>

#include <functional>

namespace Engine
{
	/**
	 * The Render pipeline is the thread that accepts and runs render tasks in the form of
	 * function objects that are put into the pipeline's work queue.  Having a single thread
	 * run rendering tasks in sequence prevents a lot of context switching that can stall a
	 * GPU pipeline, and the queueing system enables multiple threads to generate work
	 * without having to wait for access to the rendering context.
	 *
	 * Functions are executed in the order in which they are enqueued into the pipeline.  Any
	 * commands that are part of a previously submitted function can be considered complete
	 * when it comes to running code of functions submitted later.  For code outside of
	 * the context of the rendering pipeline, Fence objects can be used to determine 
	 * and sync on completion of GPU tasks.
	 *
	 * The Render namespace also contains a platform abstraction layer for many functions
	 * performed during rendering that don't neatly fit elsewhere into other classes or
	 * namespaces of the Engine, or change pipeline state.
	 */
	namespace Render
	{
		/**
		 * Enqueues a function into the Rendering pipeline.
		 */
		ENGINE_FUNC_EXPORT void enqueue(std::function<void()>&& function);

		ENGINE_FUNC_EXPORT void setTarget(GPU::RenderTarget* target);
		ENGINE_FUNC_EXPORT void swapBuffers();
		ENGINE_FUNC_EXPORT void clearTarget();
		
		ENGINE_FUNC_EXPORT void clear(unsigned int buffers);

		/**
		 * Many GPU drivers queue commands, waiting until a certian number of them
		 * have been issued before sending them in batches to the GPU.  This function
		 * causes queued commands to be sent to the GPU for execution, without waiting
		 * (possibly forever) for additional commands to fill the the command buffer.
		 *
		 * This only forces commands to be sent to the GPU for execution.  Use a Fence
		 * to determine when execution of commands is complete.
		 */
		ENGINE_FUNC_EXPORT void flush();

		/**
		 * Returns true if the current thread is the Render pipeline.
		 */
		ENGINE_FUNC_EXPORT bool inPipeline();
	}

	namespace Load
	{
		ENGINE_FUNC_EXPORT void enqueue(std::function<void()>&& function);

		/**
		 * Forces any queued commands to be sent to the GPU and blocks until they are complete. 
		 */
		ENGINE_FUNC_EXPORT void flush();

		/**
		 * Returns true if the current thread is the Load pipeline.
		 */
		ENGINE_FUNC_EXPORT bool inPipeline();
	}
}

#endif // _ENGINE_PIPELINE_H_