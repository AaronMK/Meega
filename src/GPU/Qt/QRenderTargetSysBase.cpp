#include <GPU/Internal/Qt/QRenderTargetSysBase.h>

#include <QtCore/QEvent>

#ifdef Q_OS_WIN

namespace GPU
{
	QRenderTargetSysBase::QRenderTargetSysBase(QWidget* parent, Qt::WindowFlags f)
		: QWidget(parent, f | Qt::MSWindowsOwnDC), GPU::RenderTarget(),
		mDeviceContext(NULL)
	{
		setAttribute(Qt::WA_PaintOnScreen);
	}

	QRenderTargetSysBase::~QRenderTargetSysBase()
	{
		if (mDeviceContext != NULL)
			ReleaseDC(handle(), mDeviceContext);
	}

	HWND QRenderTargetSysBase::handle()
	{
		return (HWND)winId();
	}

	HDC QRenderTargetSysBase::hdc()
	{
		if (NULL == mDeviceContext)
			mDeviceContext = GetDC(handle());

		Q_ASSERT(NULL != mDeviceContext);
		return mDeviceContext;
	};

	void QRenderTargetSysBase::changeEvent(QEvent *Evt)
	{
		if (QEvent::ParentChange == Evt->type() && mDeviceContext != NULL)
		{
			ReleaseDC(handle(), mDeviceContext);
			mDeviceContext = 0;
			handleChanged();
		}

		QWidget::changeEvent(Evt);
	}

	QPaintEngine* QRenderTargetSysBase::paintEngine() const
	{
		return nullptr;
	}
}
#else
#	error QRenderTarget is not supported on this platform.
#endif