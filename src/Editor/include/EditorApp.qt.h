#ifndef _EDITOR_APP_QT_H_
#define _EDITOR_APP_QT_H_

#include <QtWidgets/QApplication>

#include <functional>

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
};

#endif // _EDITOR_APP_QT_H_