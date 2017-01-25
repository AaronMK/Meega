#ifndef _ENGINE_PIPELINE_H_
#define _ENGINE_PIPELINE_H_

#include "Fence.h"

#include "../Core/Constants.h"

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
		 * @brief
		 *  Enqueues a function into the Rendering pipeline.
		 */
		ENGINE_EXPORT void enqueue(std::function<void()>&& function);

		/**
		 * @brief
		 *  Sets the render target.  It is not valid to call this outside of the
		 *  rendering pipeline.
		 */
		ENGINE_EXPORT void setTarget(GPU::RenderTarget* target);

		/**
		 * @brief
		 *  Defines the mapping of nomralized device coordinates to window coordinates
		 *  on the active render target.
		 */
		ENGINE_EXPORT void viewport(int left, int bottom, int width, int height);

		/**
		 * @brief
		 *  Swaps the back and front buffers of the active render target.
		 */
		ENGINE_EXPORT void swapBuffers();
		
		ENGINE_EXPORT void clearTarget();
		
		ENGINE_EXPORT void clear(unsigned int buffers);

		/**
		 * @brief
		 *  Pushes a flush command to the pipeline.
		 * 
		 *  Many GPU drivers queue commands, waiting until a certian number of them
		 *  have been issued before sending them in batches to the GPU.  This function
		 *  causes queued commands to be sent to the GPU for execution, without waiting
		 *  (possibly forever) for additional commands to fill the the command buffer.
		 *
		 *  This only forces commands to be sent to the GPU for execution.  Use a Fence
		 *  to determine when execution of commands is complete.
		 */
		ENGINE_EXPORT void flush();

		/**
		 * @brief
		 *  Returns true if the current thread is the Render pipeline.
		 */
		ENGINE_EXPORT bool inPipeline();
	}

	namespace Load
	{
		ENGINE_EXPORT void enqueue(std::function<void()>&& function);

		/**
		 * @brief
		 *  Forces any queued commands to be sent to the GPU and blocks until they are complete. 
		 */
		ENGINE_EXPORT void flush();

		/**
		 * @brief
		 *  Returns true if the current thread is the Load pipeline.
		 */
		ENGINE_EXPORT bool inPipeline();
	}
}

#endif // _ENGINE_PIPELINE_H_