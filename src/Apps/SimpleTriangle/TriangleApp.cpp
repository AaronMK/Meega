#include "TriangleApp.qt.h"

#include <Engine/Shading/Shader.h>

#include <Engine/Tasking/Scheduling.h>
#include <Engine/Tasking/Pipeline.h>
#include <Engine/Tasking/Fence.h>
#include <Engine/Timing/Timing.h>

#include <QtWidgets/QDockWidget>

#include <math.h>

using namespace Engine;
using namespace AppsCommon;

using namespace StdExt::Concurrent;

TriangleApp::TriangleApp(int argc, char** argv)
	: QApplication(argc, argv), mStop(false)
{
	mMainWindow = new QMainWindow();
	mRenderTarget = new SDK::QRenderTarget();

	mRenderTarget->setMinimumSize(640, 480);
	mMainWindow->setCentralWidget(mRenderTarget);

	connect(mRenderTarget, &SDK::QRenderTarget::resized, this, &TriangleApp::onRenderTargetResize);

	QDockWidget* settingsDock = new QDockWidget("Settings");
	settingsDock->setWidget(mTriangle.makePropertiesWidget());

	mMainWindow->addDockWidget(Qt::LeftDockWidgetArea, settingsDock);
	mMainWindow->show();

	mCamera.setLookAt(vec3(0.0f, 0.0f, -2.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

	mRenderTask = std::make_unique<FunctionTask>(
		[this]()
		{
			TriangleApp::renderLoop();
		}
	);

	Engine::ScheduleTask(mRenderTask.get(), Priority::High);
}

TriangleApp::~TriangleApp()
{
	mStop = true;
	mRenderTask->wait();
}

void TriangleApp::renderLoop()
{
	while (!mStop)
	{
		Timing::update();
		Engine::Render::enqueue([this]()
		{
			Engine::Render::setTarget(mRenderTarget);
			Engine::Render::clear(COLOR_BUFFER_BIT | DEPTH_BUFFER_BIT);

			mTriangle.draw(mCamera);

			Engine::Render::swapBuffers();
			Engine::Render::flush();
		});

		Engine::Render::fence();
	}
}

void TriangleApp::onRenderTargetResize(int width, int height)
{
	Engine::Render::enqueue([this, width, height]()
	{
		mCamera.setPerspective(30.0f, float(width), float(height), 1.0f, 100.0f);

		// float AR = float(width) / float(height);
		// mCamera.setOrthographic(-AR, AR, -1.0f, 1.0f, 1.0f, 100.0f);
		glViewport(0, 0, width, height);
	});
}