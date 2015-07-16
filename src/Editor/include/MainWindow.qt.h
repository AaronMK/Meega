#ifndef _MAIN_WINDOW_QT_H_
#define _MAIN_WINDOW_QT_H_

#include <QtWidgets/QMainWindow>

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow();
	virtual ~MainWindow();

private slots:
	void onFileNewProject(bool checked);
	void onFileOpenProject(bool checked);
};

#endif // _MAIN_WINDOW_QT_H_