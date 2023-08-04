#ifndef _EDITOR_APP_QT_H_
#define _EDITOR_APP_QT_H_

#include <StdExt/Concurrent/Producer.h>

#include <functional>
#include <memory>

#include "MainWindow.qt.h"
#include <QtWidgets/QApplication>


/**
 * Mostly singleton applciation object.  For the purposes of signals and slots there is
 * an instance function to get the QObject, but otherwise, the functionality is static.
 */
class EditorApp : public QApplication
{
	Q_OBJECT
public:
	EditorApp(int argc, char** argv);
	virtual ~EditorApp();

	static void runInGuiThread(std::function<void(void)>&& func);

	static EditorApp* instance();

signals:
	void guiThreadRunRequested();

private slots:
	void onGuiThreadRunRequested();

private:
	std::unique_ptr<MainWindow> mMainWindow;
	StdExt::Concurrent::Producer<std::function<void()>> guiFunctionQueue;
};

#endif // _EDITOR_APP_QT_H_