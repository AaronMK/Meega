#include <GPU/OpenGL/Common.h>

#if !defined(_GPU_GL_CONTEXT_SYS_BASE_H_) && defined(GPU_SUPPORT_OPEN_GL)
#define _GPU_GL_CONTEXT_SYS_BASE_H_

#include "../../OpenGL/Format.h"
#include "../../RenderTarget.h"

#if defined(_WIN32)

namespace GPU
{
	class HiddenWindow;
}

namespace OpenGL
{
	class GPU_DYNAMIC_CLASS ContextSysBase
	{
	protected:
		void init();

		void initOldContext();
		void initNewContext(HGLRC shared = 0);

		bool checkPixelFormat(GPU::RenderTargetWin *target);

		HGLRC mHGLRC;
		PIXELFORMATDESCRIPTOR mPixelFormat;

		Format mGLFormat;

		GPU::RenderTargetWin *mTarget;
		GPU::HiddenWindow* mHiddenWindow;
	};
}

#endif // _WIN32

#endif // _GPU_GL_CONTEXT_SYS_BASE_H_