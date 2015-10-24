#include "include/MainWindow.qt.h"

#include <SDK/Project/Project.h>
#include <SDK/Widgets/QCreateProjectDialog.qt.h>
#include <SDK/Internal/Project/ProjectPrivate.h>

#include <QtWidgets/QMenuBar>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QLabel>

#include <functional>

using namespace MeegaSDK;

MainWindow::MainWindow()
	: QMainWindow()
{
	QDockWidget* assetsDock = new QDockWidget(tr("Assets"), this);
	assetsDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

	QMenuBar* menuBar = new QMenuBar();
	QMenu* fileMenu = menuBar->addMenu(tr("File"));
	QMenu* projectMenu = menuBar->addMenu(tr("Project"));
	QMenu* windowMenu = menuBar->addMenu(tr("Window"));

	connect(fileMenu->addAction(tr("New Project...")), &QAction::triggered,
	        this, &MainWindow::onFileNewProject);

	connect(fileMenu->addAction(tr("Open Project...")), &QAction::triggered,
	        this, &MainWindow::onFileOpenProject);

	windowMenu->addAction(assetsDock->toggleViewAction());

	setCentralWidget(new QLabel(tr("Placeholder Widget")));
	addDockWidget(Qt::LeftDockWidgetArea, assetsDock);
	setMenuBar(menuBar);
}

MainWindow::~MainWindow()
{

}

void MainWindow::onFileNewProject(bool checked)
{
	QCreateProjectDialog dialog(this);
	
	if (QDialog::Accepted == dialog.exec())
	{
		std::unique_ptr<ProjectPrivate> projectPrivate(new ProjectPrivate());
		projectPrivate->projectDir = dialog.selectedDir;
		projectPrivate->projectName = dialog.projectName;

		std::unique_ptr<Project> project = dialog.projectPlugin->createProject(std::move(projectPrivate));
	}
}

void MainWindow::onFileOpenProject(bool checked)
{
}