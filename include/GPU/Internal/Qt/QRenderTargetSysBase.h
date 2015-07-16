#ifndef _GPU_Q_RENDER_RARGET_SYS_BASE_QT_H_
#define _GPU_Q_RENDER_RARGET_SYS_BASE_QT_H_

#include <GPU/RenderTarget.h>
#include <QtWidgets/QWidget>

#ifdef Q_OS_WIN
#	ifdef _DEBUG
#		pragma comment(lib, "Qt5Widgetsd.lib")
#		pragma comment(lib, "Qt5Cored.lib")
#	else
#		pragma comment(lib, "Qt5Widgets.lib")
#		pragma comment(lib, "Qt5Core.lib")
#	endif

namespace GPU
{
	class GPU_DYNAMIC_CLASS QRenderTargetSysBase : public QWidget, public RenderTargetWin
	{
	protected:
		QRenderTargetSysBase(QWidget* parent = 0, Qt::WindowFlags f = 0);
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