#include <SDK/Internal/Project/ProjectPrivate.h>
#include <SDK/Plugins/PluginManager.h>

#include <StdExt/Exceptions.h>

#include <QtCore/QDataStream>

using namespace StdExt;

namespace MeegaSDK
{
	ProjectPrivate::ProjectPrivate()
	{
		plugin = nullptr;
		version = 1;
	}

	ProjectPrivate::ProjectPrivate(ProjectPrivate&& other)
	{
		directory = other.directory;
		name = QString(std::move(other.name));

		plugin = other.plugin;
		other.plugin = nullptr;

		version = other.version;

		projectMenu = other.projectMenu;
		other.projectMenu = nullptr;

		file.reset(other.file.release());
	}

	ProjectPrivate::~ProjectPrivate()
	{
		close();
	}

	void ProjectPrivate::save()
	{
		if (nullptr == file.get())
		{
			file.reset(new QFile(directory.absoluteFilePath("project.meega")));

			if (false == file->open(QIODevice::ReadWrite))
			{
				file.reset(nullptr);
				throw invalid_operation(QObject::tr("Could not open or create project file.").toStdString());
			}
		}
		else
		{
			throw invalid_operation(QObject::tr("No project file is open.").toStdString());
		}

		file->resize(0);
		file->seek(0);

		QDataStream stream(file.get());
		stream << version << plugin->id() << plugin->name() << name;
	}

	void ProjectPrivate::close()
	{
		if (file)
		{
			file->close();
			file.reset(nullptr);

			plugin = nullptr;
			version = 1;

			name.clear();
			directory = QDir();
		}
	}

	void ProjectPrivate::load(QDir dir)
	{
		if (nullptr != file.get())
			throw invalid_operation(QObject::tr("A project file is already open.").toStdString());

		directory = dir;
		std::unique_ptr<QFile> openedFile(new QFile(directory.absoluteFilePath("project.meega")));

		if (false == openedFile->exists())
			throw invalid_operation(QObject::tr("A project file does not exist in the selected directory.").toStdString());

		if (false == openedFile->open(QIODevice::ReadWrite))
			throw filesystem_error(QObject::tr("Could not open the project file with write permissions.").toStdString());

		QDataStream stream(openedFile.get());
		uint32_t inPluginId = PluginId::INVALID;
		QString inPluginName;

		stream >> version;
		if (version > 1)
		{
			version = 0;
			throw std::domain_error(QObject::tr("The file was created with a newer version of the software.").toStdString());
		}

		stream >> inPluginId;
		
		Plugin* inPlugin = PluginManager::getPluginById(inPluginId);

		if (nullptr == inPlugin)
		{
			stream >> inPluginName;
			throw std::domain_error(QObject::tr("The plugin %1 has not been loaded.").arg(inPluginName).toStdString());
		}
		
		if (Plugin::Type::Project != inPlugin->type())
			throw std::domain_error(QObject::tr("There is an error in the plugin specified by the file or the plugin is misidentified.").toStdString());

		plugin = dynamic_cast<ProjectPlugin*>(inPlugin);
		stream >> name;

		file.reset(openedFile.release());
	}
}