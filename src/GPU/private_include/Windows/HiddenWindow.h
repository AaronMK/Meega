#ifndef _GPU_HIDDEN_WINDOW_H_
#define _GPU_HIDDEN_WINDOW_H_

#include <GPU/Windows/RenderTargetWin.h>

namespace GPU
{
	/**
	 * @internal
	 *
	 * All Windows OpenGL contexts require a window as a target when they are made current.
	 * This class encapsulates a dummy window which can be 
	 *
	 * A class that encapsulates a native WIN32 window suitable as a target for a "headless" context.
	 * These are used to create temporary contexts, or as a home for a pBuffer.  They are not
	 * meant to be visible.
	 */
	class GPU_DYNAMIC_CLASS HiddenWindow : public RenderTargetWin
	{
	public:

		/**
		 * Initializes shared data for hidden render targets.
		 */
		static bool initialize();

		static void shutdown();

		HiddenWindow();
		virtual ~HiddenWindow();

		virtual HWND handle();
		virtual HDC hdc();

		virtual void getDims(int *outWidth, int *outHeight);

	private:
		static const int winSize = 8;

		HWND m_Handle;
		HDC m_DeviceContext;
	};
};

#endif // _GPU_HIDDEN_WINDOW_H_