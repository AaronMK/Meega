#include <SDK/Widgets/QCreateProjectDialog.qt.h>

#include <SDK/Plugins/PluginManager.h>

#include <QtWidgets/QFileDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QDialogButtonBox>

Q_DECLARE_METATYPE(MeegaSDK::ProjectPlugin*);

namespace MeegaSDK
{
	QCreateProjectDialog::QCreateProjectDialog(QWidget* parent)
		: QDialog(parent), projectPlugin(nullptr)
	{
		pluginSelectModel = new QStandardItemModel();

		QVector<ProjectPlugin*> plugins = PluginManager::getProjectPlugins();
		Q_FOREACH(ProjectPlugin* plugin, plugins)
		{
			QStandardItem* pluginItem = new QStandardItem(plugin->name());
			pluginItem->setData(QVariant::fromValue<ProjectPlugin*>(plugin), Qt::UserRole);

			pluginSelectModel->appendRow(pluginItem);
		}

		listView = new QListView();
		listView->setMinimumSize(300, 200);
		listView->setModel(pluginSelectModel);
		listView->setSelectionBehavior(QAbstractItemView::SelectRows);
		listView->setSelectionMode(QAbstractItemView::SingleSelection);
		listView->setCurrentIndex(QModelIndex());

		lineName = new QLineEdit();
		lineRootFolder = new QLineEdit();

		QPushButton* buttonBrowse = new QPushButton(tr("Browse..."));

		QDialogButtonBox* dialogButtons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

		QHBoxLayout* layoutDirSelect = new QHBoxLayout();
		layoutDirSelect->addWidget(lineRootFolder, 1);
		layoutDirSelect->addWidget(buttonBrowse, 0);
		
		QFormLayout* layoutOptions = new QFormLayout();
		layoutOptions->addRow(tr("Name:"), lineName);
		layoutOptions->addRow(tr("Folder:"), layoutDirSelect);

		QVBoxLayout* layoutMain = new QVBoxLayout();
		layoutMain->addWidget(listView, 1);
		layoutMain->addLayout(layoutOptions, 0);
		layoutMain->addWidget(dialogButtons, 0);

		setLayout(layoutMain);

		connect(buttonBrowse, &QPushButton::clicked, this, &QCreateProjectDialog::onBrowseButton);
		connect(dialogButtons, &QDialogButtonBox::accepted, this, &QCreateProjectDialog::onAccepted);
		connect(dialogButtons, &QDialogButtonBox::rejected, this, &QCreateProjectDialog::onRejected);
	}

	QCreateProjectDialog::~QCreateProjectDialog()
	{

	}

	void QCreateProjectDialog::onBrowseButton(bool checked)
	{
		QString directory = QFileDialog::getExistingDirectory(this);
		
		if (QDir(directory).exists())
			lineRootFolder->setText(directory);
	}
	
	void QCreateProjectDialog::onRejected()
	{
		projectName = "";
		selectedDir = QDir();
		projectPlugin = nullptr;

		reject();
	}
	
	void QCreateProjectDialog::onAccepted()
	{
		projectName = lineName->text();
		selectedDir = QDir(lineRootFolder->text());

		// Check that a plugin was selected.
		QModelIndex selectedIndex = listView->currentIndex();
		if (selectedIndex.isValid())
		{
			projectPlugin = pluginSelectModel->data(selectedIndex, Qt::UserRole).value<ProjectPlugin*>();
		}
		else
		{
			QMessageBox::information(this, tr("Field Error"), tr("A project type must be selected."));
			return;
		}

		// Check that there is a valid name for the project.
		if (projectName.trimmed() == "")
		{
			QMessageBox::information(this, tr("Field Error"), tr("A name must be entered for the project."));
			return;
		}

		// Check that the directory is an absolute path.
		if (!selectedDir.isAbsolute())
		{
			QMessageBox::information(this, tr("Field Error"), tr("The project direcotry must be an absolute path."));
			return;
		}

		// Check that the selected directory exists.
		if (!selectedDir.exists() && !selectedDir.mkpath(lineRootFolder->text()))
		{
			QMessageBox::information(this, tr("Field Error"), tr("Attempt to create the project directory failed."));
			return;
		}

		// Check that the selected directory is empty.
		if ( selectedDir.entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries | QDir::Hidden | QDir::System).count() != 0 )
		{
			QMessageBox::information(this, tr("Field Error"), tr("The project directory must be empty."));
			return;
		}

		accept();
	}
}