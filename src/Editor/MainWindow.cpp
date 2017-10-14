#include "include/MainWindow.qt.h"

#include <SDK/Project/Project.h>
#include <SDK/Widgets/QCreateProjectDialog.qt.h>
#include <SDK/Internal/Project/ProjectPrivate.h>

#include <QtWidgets/QDockWidget>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QLabel>

#include <functional>

using namespace MeegaSDK;

MainWindow::MainWindow()
	: QMainWindow()
{
	QDockWidget* assetsDock = new QDockWidget(tr("Assets"), this);
	assetsDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

	mMenuBar = new QMenuBar();
	mFileMenu = mMenuBar->addMenu(tr("File"));
	mProjectMenu = mMenuBar->addMenu(tr("Project"));
	mWindowMenu = mMenuBar->addMenu(tr("Window"));

	mProjectMenu->setDisabled(true);

	connect(mFileMenu->addAction(tr("New Project...")), &QAction::triggered,
	        this, &MainWindow::onFileNewProject);

	connect(mFileMenu->addAction(tr("Open Project...")), &QAction::triggered,
	        this, &MainWindow::onFileOpenProject);

	mWindowMenu->addAction(assetsDock->toggleViewAction());

	setCentralWidget(new QLabel(tr("Placeholder Widget")));
	addDockWidget(Qt::LeftDockWidgetArea, assetsDock);
	setMenuBar(mMenuBar);
}

MainWindow::~MainWindow()
{

}

void MainWindow::onFileNewProject(bool checked)
{
	QCreateProjectDialog::createProject(this);
}

void MainWindow::onFileOpenProject(bool checked)
{
	try
	{
		std::unique_ptr<ProjectPrivate> projPrivate(new ProjectPrivate());
		projPrivate->projectMenu = mProjectMenu;

		QString directory = QFileDialog::getExistingDirectory(this);
		Project::openProject(QDir(directory), std::move(projPrivate));

		if (mProjectMenu->children().count() > 0)
			mProjectMenu->setEnabled(true);
	}
	catch (std::exception& ex)
	{
		QMessageBox::critical(this, QObject::tr("Project Open Error"), ex.what());
	}
}