#include <GPU/Internal/OpenGL/ContextSysBase.h>

#ifdef _WIN32

#include "../private_include/Windows/HiddenWindow.h"

namespace OpenGL
{
	void ContextSysBase::init()
	{
		mHiddenWindow = new GPU::HiddenWindow();

		memset(&mPixelFormat, 0, sizeof(PIXELFORMATDESCRIPTOR));

		mPixelFormat.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		mPixelFormat.nVersion = 1;
		mPixelFormat.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		mPixelFormat.iPixelType = PFD_TYPE_RGBA;
		mPixelFormat.cColorBits = 32;
		mPixelFormat.cDepthBits = 24;
		mPixelFormat.cStencilBits = 8;
		mPixelFormat.iLayerType = PFD_MAIN_PLANE;
	}

	void ContextSysBase::initOldContext()
	{
		if (checkPixelFormat(mHiddenWindow))
			mHGLRC = wglCreateContext(mHiddenWindow->hdc());
		else
			mHGLRC = 0;
	}

	void ContextSysBase::initNewContext(HGLRC shared)
	{
		int compatibilityBit = (mGLFormat.versionProfile == Profile::CORE)
			? WGL_CONTEXT_CORE_PROFILE_BIT_ARB : WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB;

		int contextFlags = 0;

		if (mGLFormat.debug)
			contextFlags |= WGL_CONTEXT_DEBUG_BIT_ARB;

		int attribList[] =
		{
			WGL_CONTEXT_MAJOR_VERSION_ARB, mGLFormat.versionMajor,
			WGL_CONTEXT_MINOR_VERSION_ARB, mGLFormat.versionMinor,
			WGL_CONTEXT_FLAGS_ARB, contextFlags,
			WGL_CONTEXT_PROFILE_MASK_ARB, compatibilityBit,
			0
		};

		// Context creation failed when the profile bit was not applicable.  If that is the case
		// (versions 3.1 and below), we zero the parameter that would have signified a compatibility
		// parameter so it instead marks the end of the list.
		if (mGLFormat.versionMajor < 3 || (mGLFormat.versionMajor == 3 && mGLFormat.versionMinor < 2))
			attribList[6] = 0;

		if (checkPixelFormat(mHiddenWindow))
			mHGLRC = wglCreateContextAttribsARB(mHiddenWindow->hdc(), shared, attribList);
		else
			mHGLRC = 0;
	}

	bool ContextSysBase::checkPixelFormat(GPU::RenderTargetWin *target)
	{
		if (0 == target->mPixelFormatId)
		{
			target->mPixelFormatId = ChoosePixelFormat(target->hdc(), &mPixelFormat);
			if (FALSE == SetPixelFormat(target->hdc(), target->mPixelFormatId, &(mPixelFormat)))
				return false;
		}

		return true;
	}
}

#endif // _WIN32