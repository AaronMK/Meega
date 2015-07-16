#include "include/MainWindow.qt.h"

#include <QtWidgets/QMenuBar>

#include <functional>

MainWindow::MainWindow()
	: QMainWindow()
{
	QMenuBar* menuBar = new QMenuBar();
	QMenu* fileMenu = menuBar->addMenu(tr("File"));
	QMenu* projectMenu = menuBar->addMenu(tr("Project"));
	QMenu* windowMenu = menuBar->addMenu(tr("Window"));

	connect(fileMenu->addAction(tr("New Project...")), &QAction::triggered,
	        this, &MainWindow::onFileNewProject);

	connect(fileMenu->addAction(tr("Open Project...")), &QAction::triggered,
	        this, &MainWindow::onFileOpenProject);

	setMenuBar(menuBar);
}

MainWindow::~MainWindow()
{

}


void MainWindow::onFileNewProject(bool checked)
{

}

void MainWindow::onFileOpenProject(bool checked)
{

}