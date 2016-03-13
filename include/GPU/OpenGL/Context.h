#include <GPU/Config.h>

#if !defined(_GPU_GL_CONTEXT_H_) && defined(GPU_SUPPORT_OPEN_GL)
#define _GPU_GL_CONTEXT_H_

#include "../Internal/OpenGL/ContextSysBase.h"

namespace OpenGL
{
	/**
	 * @brief
	 *  An OpenGL context, abstracting system specific functionality.
	 */
	class GPU_DYNAMIC_CLASS Context : public ContextSysBase
	{
	public:
		Context(const Context&) = delete;

		/**
		 * @brief
		 *  Creates a context with the supplied format on target.  If target is NULL,
		 *  the context will be attached to an invisible window.
		 */
		Context(const Format &fmnt);

		/**
		 * @brief
		 *  Creates a shared context. If target is NULL, the context will be attached
		 *  to an invisible window.
		 *
		 *  <B>The shared context must be current when this constructor is called.</B>
		 */
		Context(Context *shared);

		virtual ~Context();

		/**
		 * @brief
		 *  Makes the context the current context for the thread. 
		 */
		virtual bool makeCurrent(GPU::RenderTarget *target = nullptr);

		/**
		 * @brief
		 *  Releases the context from the thread.
		 */
		virtual void doneCurrent();

		/**
		 * @brief
		 *  This begins the process of swapping the front an back buffers of the context.  The context should be current
		 *  when this is called.
		 */
		void swapBuffers();

		/**
		 * @brief
		 *  Gets a pointer to the current context of the thread.
		 */
		static Context* current();
	};
}


#endif // _GPU_GL_CONTEXT_H_