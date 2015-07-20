#include "include/EditorApp.qt.h"
#include "include/MainWindow.qt.h"

#if defined(_WIN32)
#	pragma comment(lib, "Concurrent.lib")
#endif // WIN_32

#include <Concurrent/Producer.h>

static MainWindow* mainWindow = nullptr;
static Concurrent::Producer<std::function<void ()>> guiFunctionQueue;

EditorApp::EditorApp(int argc, char** argv)
	: QApplication(argc, argv)
{
	mainWindow = new MainWindow;
	mainWindow->show();

	connect(this, &EditorApp::guiThreadRunRequested, &EditorApp::onGuiThreadRunRequested);
}

EditorApp::~EditorApp()
{
	guiFunctionQueue.end();
	delete mainWindow;
}

EditorApp* EditorApp::instance()
{
	return dynamic_cast<EditorApp*>(qApp);
}

void EditorApp::runInGuiThread(std::function<void(void)>&& func)
{
	guiFunctionQueue.push(std::forward <std::function<void()>>(func));
	emit instance()->guiThreadRunRequested();
}

void EditorApp::onGuiThreadRunRequested()
{
	std::function<void()> func;
	if (guiFunctionQueue.consume(func))
	{
		func();
	}
}