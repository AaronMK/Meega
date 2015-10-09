#ifndef _GPU_Q_RENDER_RARGET_QT_H_
#define _GPU_Q_RENDER_RARGET_QT_H_

#include "../Internal/Qt/QRenderTargetSysBase.h"

namespace GPU
{
	class GPU_DYNAMIC_CLASS QRenderTarget : public QRenderTargetSysBase
	{
		Q_OBJECT
	public:
		QRenderTarget(QWidget* parent = 0, Qt::WindowFlags f = 0);
		virtual ~QRenderTarget();

		virtual void getDims(int *outWidth, int *outHeight) override;

	signals:
		void resized(int width, int height);

	protected:
		virtual void resizeEvent(QResizeEvent *Evt) override;
	};
}

#endif // _GPU_Q_RENDER_RARGET_QT_H_