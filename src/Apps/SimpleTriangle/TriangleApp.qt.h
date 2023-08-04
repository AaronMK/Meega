#ifndef _TRAINGLE_APP_
#define _TRAINGLE_APP_

#include <SDK/Widgets/QRenderTarget.qt.h>

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

#include <StdExt/Concurrent/FunctionTask.h>

#include <Engine/Tasking/Fence.h>
#include <Engine/Camera/Camera.h>

#include "Triangle.h"

#include <memory>

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

	std::unique_ptr<StdExt::Concurrent::FunctionTask> mRenderTask;

	bool mStop;

	QMainWindow* mMainWindow;
	SDK::QRenderTarget* mRenderTarget;

	Triangle mTriangle;

	Engine::Camera mCamera;
};

#endif // _TRAINGLE_APP_