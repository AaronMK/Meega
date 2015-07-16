#include <GPU/Config.h>

#if defined(GPU_SUPPORT_OPEN_GL)

#include <GPU/OpenGL/Context.h>

#include "../private_include/Windows/HiddenWindow.h"

#include <cassert>
#include <string>

#ifdef _WIN32

__declspec(thread) OpenGL::Context* currentContext = nullptr;
__declspec(thread) WGLEWContext* currentWGLEW = nullptr;
__declspec(thread) GLEWContext* currentGLEW = nullptr;

WGLEWContext* wglewGetContext()
{
	return currentWGLEW;
}

GLEWContext* glewGetContext()
{
	return currentGLEW;
}

namespace OpenGL
{
	Context::Context(const Format &fmnt)
		: ContextSysBase()
	{
		mTarget = nullptr;
		mGLFormat = fmnt;

		init();

		if ( mGLFormat.versionMajor >= 3 )
		{
			// Use a "sppringboard" context used to create an
			// OpenGL 3.0 or greater context.
			Format tempFormat;
			tempFormat.versionMajor = 2;
			tempFormat.versionMinor = 1;
			tempFormat.versionProfile = Profile::COMPATIBILITY;

			Context tempContext(tempFormat);

			tempContext.makeCurrent();
			initNewContext();
			tempContext.doneCurrent();
		}
		else
		{
			// Simply initialize an old context for our window.
			initOldContext();
		}

		// GLEW initialization.
		makeCurrent();
		{
			GLenum wglewInitResult = wglewInit();
			GLenum glewInitResult = glewInit();
			assert(GLEW_OK == wglewInitResult && GLEW_OK == glewInitResult);
		}
		doneCurrent();
	}
	
	Context::Context(Context *shared)
		: ContextSysBase()
	{
		assert( Context::current() == shared );

		mTarget = nullptr;
		mGLFormat = shared->mGLFormat;
		GPU::RenderTargetWin* previousSharedTarget = shared->mTarget;
		
		init();

		if ( shared->mGLFormat.versionMajor >= 3 )
		{
			initNewContext(shared->mHGLRC);
		}
		else
		{
			initOldContext();
			wglShareLists(shared->mHGLRC, mHGLRC);
		}

		shared->doneCurrent();

		makeCurrent();
		{
			GLenum wglewInitResult = wglewInit();
			GLenum glewInitResult = glewInit();
			assert(GLEW_OK == wglewInitResult && GLEW_OK == glewInitResult);
		}
		doneCurrent();

		shared->makeCurrent(previousSharedTarget);
	}

	Context::~Context()
	{
		doneCurrent();
		wglDeleteContext(mHGLRC);

		delete mHiddenWindow;
	}

	bool Context::makeCurrent(GPU::RenderTarget *target)
	{
		// If the target is null, we are really making the target the hidden window.
		if ( nullptr == target )
			target = mHiddenWindow;

		// Check if the context is already cunrrent on the passed target.
		if ( mTarget == target && this == currentContext )
			return true;

		if ( nullptr != mTarget )
			doneCurrent();

		if ( false == checkPixelFormat(target) )
			return false;

		if ( TRUE == wglMakeCurrent(target->hdc(), mHGLRC) )
		{
			mTarget = target;
			currentContext = this;

			currentGLEW = &mGlewCtxt;
			currentWGLEW = &mWGlewCtxt;

			return true;
		}
		else
		{
			 LPVOID lpMsgBuf;
			 DWORD dw = GetLastError(); 

			 FormatMessage(
				FORMAT_MESSAGE_ALLOCATE_BUFFER | 
				FORMAT_MESSAGE_FROM_SYSTEM |
				FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL,
				dw,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				(LPTSTR) &lpMsgBuf,
				0, NULL );

			// Display the error message and exit the process
			std::string strMessage((char*)lpMsgBuf);
			LocalFree(lpMsgBuf);
		}

		return false;
	}

	void Context::doneCurrent()
	{
		wglMakeCurrent(NULL, NULL);
		mTarget = NULL;
		
		currentContext = NULL;
		currentGLEW = NULL;
		currentWGLEW = NULL;
	}

	void Context::swapBuffers()
	{
		assert( this == current() );
		SwapBuffers(mTarget->hdc());
	}

	Context* Context::current()
	{
		return currentContext;
	}
}

#endif // _WIN32

#endif // defined(_WIN32) && defined(GPU_SUPPORT_OPEN_GL)