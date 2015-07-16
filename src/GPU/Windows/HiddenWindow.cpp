#include "../private_include/Windows/HiddenWindow.h"

#include <assert.h>
#include <stdio.h>

#include <mutex>
#include <atomic>

namespace GPU
{
	/**
	 * @internal
	 */
	static char className[256];

	/**
	 * @internal
	 */
	static WNDCLASS wndClass;

	static std::mutex syncLock;
	static std::atomic<int> refCount(0);

	bool HiddenWindow::initialize()
	{
		std::lock_guard<std::mutex> lock(syncLock);

		if (0 == refCount.fetch_add(1))
		{
			memset(className, 0, sizeof(className));
			int nameAttempt = 0;

			wndClass.style = CS_OWNDC;
			wndClass.lpfnWndProc = DefWindowProc;
			wndClass.cbClsExtra = 0;
			wndClass.cbWndExtra = 0;
			wndClass.hInstance = GetModuleHandle(NULL);
			wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
			wndClass.hCursor = LoadIcon(NULL, IDC_ARROW);
			wndClass.hbrBackground = NULL;
			wndClass.lpszMenuName = NULL;
			wndClass.lpszClassName = className;

			do
			{
				sprintf_s(className, sizeof(className), "GPU_HiddenWindow_%d", nameAttempt++);
			}
			while (0 == RegisterClass(&wndClass));
		}

		return true;
	}

	void HiddenWindow::shutdown()
	{
		std::lock_guard<std::mutex> lock(syncLock);

		if (0 == refCount.fetch_sub(1))
		{
			UnregisterClass(wndClass.lpszClassName, wndClass.hInstance);
		}
	}

	HiddenWindow::HiddenWindow()
		: RenderTargetWin(), m_DeviceContext(NULL)
	{
		m_Handle = CreateWindow(wndClass.lpszClassName,
		                        NULL,
		                        WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		                        0, 0, winSize, winSize,
		                        NULL, NULL, wndClass.hInstance,
		                        NULL);
	}

	HiddenWindow::~HiddenWindow()
	{
		ReleaseDC(m_Handle, m_DeviceContext);
		DestroyWindow(m_Handle);
	}

	void HiddenWindow::getDims(int *outWidth, int *outHeight)
	{
		*outWidth = winSize;
		*outHeight = winSize;
	}

	HWND HiddenWindow::handle()
	{
		return m_Handle;
	}

	HDC HiddenWindow::hdc()
	{
		if ( NULL == m_DeviceContext )
			m_DeviceContext = GetDC(m_Handle);

		return m_DeviceContext;
	}
}