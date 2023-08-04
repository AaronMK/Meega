#include "include/EditorApp.qt.h"
#include "include/MainWindow.qt.h"

#if defined(_WIN32)
#	pragma comment(lib, "Engine.lib")
#endif // WIN_32

#include <SDK/Plugins/PluginManager.h>

using namespace MeegaSDK;

EditorApp::EditorApp(int argc, char** argv)
	: QApplication(argc, argv)
{
	mMainWindow.reset(new MainWindow);
	mMainWindow->show();

	connect(this, &EditorApp::guiThreadRunRequested, &EditorApp::onGuiThreadRunRequested);

	PluginManager::loadStandardPlugins();
}

EditorApp::~EditorApp()
{
	guiFunctionQueue.end();
}

EditorApp* EditorApp::instance()
{
	return dynamic_cast<EditorApp*>(qApp);
}

void EditorApp::runInGuiThread(std::function<void(void)>&& func)
{
	instance()->guiFunctionQueue.push(std::forward<std::function<void()>>(func));
	emit instance()->guiThreadRunRequested();
}

void EditorApp::onGuiThreadRunRequested()
{
	try
	{
		std::function<void()> func;
		guiFunctionQueue.consume(func);

		func();
	}
	catch ( ... )
	{
	}
}