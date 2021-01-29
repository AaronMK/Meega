#ifndef _GPU_Q_RENDER_RARGET_SYS_BASE_QT_H_
#define _GPU_Q_RENDER_RARGET_SYS_BASE_QT_H_

#include "../../Config.h"

#include <GPU/RenderTarget.h>

#include <QtWidgets/QWidget>

#ifdef Q_OS_WIN
#	ifdef _DEBUG
#		pragma comment(lib, "Qt6Widgetsd.lib")
#		pragma comment(lib, "Qt6Cored.lib")
#	else
#		pragma comment(lib, "Qt6Widgets.lib")
#		pragma comment(lib, "Qt6Core.lib")
#	endif

namespace SDK
{
	class MEEGA_SDK_CLASS QRenderTargetSysBase : public QWidget, public GPU::RenderTargetWin
	{
	protected:
		QRenderTargetSysBase(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
		virtual ~QRenderTargetSysBase();

	public:
		virtual void getDims(int *outWidth, int *outHeight) = 0;

		virtual HWND handle() override;
		virtual HDC hdc() override;

		virtual QPaintEngine* paintEngine() const override;

	protected:
		virtual void changeEvent(QEvent *Evt) override;

	private:
		HDC mDeviceContext;
	};
}
#else
#	error QRenderTarget is not supported on this platform.
#endif

#endif // _GPU_Q_RENDER_RARGET_SYS_BASE_QT_H_