#ifndef _EDITOR_APP_QT_H_
#define _EDITOR_APP_QT_H_

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
};

#endif // _EDITOR_APP_QT_H_