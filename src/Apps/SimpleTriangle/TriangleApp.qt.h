#ifndef _TRAINGLE_APP_
#define _TRAINGLE_APP_

#include <GPU/Qt/QRenderTarget.qt.h>

#include <QtCore/QTimer>

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

#include <GPU/Qt/QRenderTarget.qt.h>

#include <GPU/OpenGL/OpenGL.h>
#include <GPU/OpenGL/Context.h>

#include <Concurrent/FunctionTask.h>
#include <Concurrent/Producer.h>

#include <Engine/Memory/VertexArrayObject.h>
#include <Engine/Memory/VertexBufferObject.h>

#include <AppsCommon/BasicShader.h>

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
	Concurrent::FunctionTask renderTask;

	bool mStop;

	QMainWindow* mMainWindow;
	GPU::QRenderTarget* mRenderTarget;

	Engine::VAO mVertArrayObj;
	Engine::VBO mVertBuffer;
	Engine::VBO mColorBuffer;

	AppsCommon::BasicShader mBasicShader;
};

#endif // _TRAINGLE_APP_