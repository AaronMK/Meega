#ifndef _MEEGA_SDK_Q_CREATE_PROJECT_DIALOG_H_
#define _MEEGA_SDK_Q_CREATE_PROJECT_DIALOG_H_

#include "../Config.h"

#include "../Plugins/ProjectPlugin.h"

#include <QtWidgets/QDialog>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>

#include <QtGui/QStandardItemModel>

#include <QtCore/QDir>

namespace MeegaSDK
{
	class MEEGA_SDK_CLASS QCreateProjectDialog : public QDialog
	{
		Q_OBJECT
	public:
		QCreateProjectDialog(QWidget* parent = 0);
		virtual ~QCreateProjectDialog();

		QDir selectedDir;
		QString projectName;
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