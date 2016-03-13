#if !defined(_GPU_WIN_RENDER_TARGET_H_) && defined(_WIN32)
#define _GPU_WIN_RENDER_TARGET_H_

#include "../Config.h"

#include <Windows.h>

namespace OpenGL
{
	class ContextSysBase;
}

namespace GPU
{
	/**
	 * @brief
	 *  Defines the base functionality of a render target on the Windows platform, regardless
	 *  of the graphics API being used. For windows, this means the addition of a function to
	 *  obtain an HWND for a context to use.
	 */
	class GPU_DYNAMIC_CLASS RenderTargetWin
	{
		friend class OpenGL::ContextSysBase;
	public:
		
		/**
		 * @brief
		 *  Do base setup for a render target suitable for both DirextX and OpenGL rendering.
		 */
		RenderTargetWin();
		
		virtual ~RenderTargetWin();

		/**
		 * @brief
		 *  Obtains the pixel dimensions of the render target.
		 */
		virtual void getDims(int *outWidth, int *outHeight) = 0;

		/**
		 * @brief
		 *  Obtains a handle used by contexts to link to a render target.
		 */
		virtual HWND handle() = 0;

		/**
		 * @brief
		 *  Gets the device context of the window.  It is assumed that the window itself manages
		 *  the returned device context.
		 */
		virtual HDC hdc() = 0;

		/**
		 * @brief
		 *  This MUST be called if the window id changes
		 */
		void handleChanged();

	private:
		int mPixelFormatId;
	};
}

#endif // _GPU_WIN_RENDER_TARGET_H_