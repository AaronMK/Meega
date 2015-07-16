#include "include/EditorApp.qt.h"

#include "include/MainWindow.qt.h"

static MainWindow* mainWindow = nullptr;

EditorApp::EditorApp(int argc, char** argv)
	: QApplication(argc, argv)
{
	mainWindow = new MainWindow;
	mainWindow->show();
}

EditorApp::~EditorApp()
{
	delete mainWindow;
}