#ifndef _TRAINGLE_APP_
#define _TRAINGLE_APP_

#include <SDK/Widgets/QRenderTarget.qt.h>

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

#include <StdExt/Concurrent/FunctionTask.h>

#include <Engine/Tasking/Fence.h>
#include <Engine/Camera/Camera.h>

#include "Triangle.h"

class TriangleApp : public QApplication
{
	Q_OBJECT
public:
	TriangleApp(int argc, char** argv);
	virtual ~TriangleApp();

private slots:
	void onRenderTargetResize(int width, int height);

private:
	void renderLoop();
	StdExt::Concurrent::FunctionTask renderTask;

	bool mStop;

	QMainWindow* mMainWindow;
	SDK::QRenderTarget* mRenderTarget;

	Triangle mTriangle;

	Engine::Camera mCamera;
	Engine::Fence mRenderFence;
};

#endif // _TRAINGLE_APP_