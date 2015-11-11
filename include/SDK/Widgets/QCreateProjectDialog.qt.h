#ifndef _MEEGA_SDK_Q_CREATE_PROJECT_DIALOG_H_
#define _MEEGA_SDK_Q_CREATE_PROJECT_DIALOG_H_

#include "../Config.h"

#include "../Plugins/ProjectPlugin.h"

#include <QtWidgets/QDialog>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtGui/QStandardItemModel>
#include <QtCore/QDir>

#include <memory>

namespace MeegaSDK
{
	class ProjectPrivate;

	/**
	 * @brief
	 *   A dialog for getting the base parameters necessary from the user to create a new project.
	 *
	 *   This dialog will present the user with ProjectPlugin classes that have been loaded, and prompt
	 *   for other information common to all projects.  That information will be used to create the
	 *   opaque projectPrivate structure object, which along with the projectPlugin, can be used
	 *   to construct the actual project.
	 *
	 *   The static createProject() provides a more streamlined approach, presenting the dialog to the
	 *   user, running all steps necessary to gain both base and plugin specific information needed
	 *   and creating the project on disk, returning the resulting Project if not canceled.
	 */
	class MEEGA_SDK_CLASS QCreateProjectDialog : public QDialog
	{
		Q_OBJECT
	public:
		static std::unique_ptr<Project> createProject(QWidget* parent = 0);

		QCreateProjectDialog(QWidget* parent = 0);
		virtual ~QCreateProjectDialog();

		std::unique_ptr<ProjectPrivate> projectPrivate;
		ProjectPlugin* projectPlugin;

	private slots:
		void onBrowseButton(bool checked);
		void onAccepted();
		void onRejected();

	private:
		QStandardItemModel* pluginSelectModel;
		QLineEdit* lineName;
		QLineEdit* lineRootFolder;
		QListView* listView;
	};
}

#endif // _MEEGA_SDK_Q_CREATE_PROJECT_DIALOG_H_