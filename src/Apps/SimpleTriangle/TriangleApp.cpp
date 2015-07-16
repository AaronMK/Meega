#include "TriangleApp.qt.h"

#include <Engine/Shading/Shader.h>

#include <Engine/Tasking/Scheduling.h>
#include <Engine/Tasking/Pipeline.h>
#include <Engine/Tasking/Fence.h>

#include <Engine/Memory/Arena.h>

#include <Concurrent/Scheduler.h>

using namespace Engine;
using namespace Concurrent;
using namespace AppsCommon;

class A
{
public:
	int mA;

	A(int a)
	{
		mA = a;
	}

	~A()
	{
		mA = 1;
	}
};

class B
{
public:
	int mA;
	int mB;

	B(int a, int b)
	{
		mA = a;
	}

	~B()
	{
		mA = 1;
	}
};


TriangleApp::TriangleApp(int argc, char** argv)
	: QApplication(argc, argv), mStop(false)
{
	Arena arena(1024);

	arena.Push<A>(2);
	arena.PushAligned<B>(16, 2, 3);
	arena.Push<B>(2, 3);

	arena.clear();

	mMainWindow = new QMainWindow();
	mRenderTarget = new GPU::QRenderTarget();

	mRenderTarget->setMinimumSize(640, 480);
	mMainWindow->setCentralWidget(mRenderTarget);

	connect(mRenderTarget, &GPU::QRenderTarget::resized, this, &TriangleApp::onRenderTargetResize);

	mMainWindow->show();

	Engine::Render::enqueue([this]()
	{
		float positionData[] =
		{
			-0.8f, -0.8f, 0.0f,
			 0.8f, -0.8f, 0.0f,
			 0.0f, 0.8f, 0.0f
		};

		float colorData[] =
		{
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f
		};

		VBO::bind(&mVertBuffer, VBO::Target::Array);
		VBO::BufferData(VBO::Target::Array, 9 * sizeof(float), positionData, VBO::Usage::StaticDraw);

		VBO::bind(&mColorBuffer, VBO::Target::Array);
		VBO::BufferData(VBO::Target::Array, 9 * sizeof(float), colorData, VBO::Usage::StaticDraw);
		VBO::unbind(VBO::Target::Array);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_NORMALIZE);

		glClearColor(0.0, 0.0, 0.0, 0.0);

		VAO::bind(&mVertArrayObj);

		VAO::enableAttribArray(0);
		VBO::bind(&mVertBuffer, VBO::Target::Array);
		VAO::attribPointerFloat(0, 3, false, 0, 0);

		VAO::enableAttribArray(1);
		VBO::bind(&mColorBuffer, VBO::Target::Array);
		VAO::attribPointerFloat(1, 3, false, 0, 0);

		VBO::unbind(VBO::Target::Array);
		VAO::unbind();
	});

	renderTask.setFunction(std::bind(&TriangleApp::renderLoop, this));
	Engine::ScheduleTask(&renderTask, Priority::High);
}

TriangleApp::~TriangleApp()
{
	mStop = true;
	renderTask.wait();
}

void TriangleApp::renderLoop()
{
	Engine::Fence fence;

	while (!mStop)
	{
		Engine::Render::enqueue([this, &fence]()
		{
			Engine::Render::setTarget(mRenderTarget);
			Engine::Render::clear(COLOR_BUFFER_BIT | DEPTH_BUFFER_BIT);

			Program::use(mBasicShader);

			VAO::bind(&mVertArrayObj);
			VAO::drawArrays(VAO::Mode::Triangles, 0, 3);
			VAO::unbind();

			mBasicShader.unload();

			fence.activate();
			Engine::Render::swapBuffers();
			Engine::Render::flush();
		});

		fence.wait();
	}
}

void TriangleApp::onRenderTargetResize(int width, int height)
{
	Engine::Render::enqueue([width, height]()
	{
		glViewport(0, 0, width, height);
	});
}