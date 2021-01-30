#include <SDK/Widgets/QRenderTarget.qt.h>

namespace SDK
{
	QRenderTarget::QRenderTarget(QWidget* parent, Qt::WindowFlags f)
		: QRenderTargetSysBase(parent, f)
	{
	}

	QRenderTarget::~QRenderTarget()
	{
	}

	void QRenderTarget::getDims(int *outWidth, int *outHeight)
	{
		*outWidth = width();
		*outHeight = height();
	}

	void QRenderTarget::resizeEvent(QResizeEvent *Evt)
	{
		emit resized(width(), height());
	};
}