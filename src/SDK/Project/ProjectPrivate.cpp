#include <SDK/Internal/Project/ProjectPrivate.h>

#include <SDK/Plugins/PluginManager.h>

#include <QtCore/QDataStream>

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
		name = other.name;

		plugin = other.plugin;
		version = other.version;

		file.reset(other.file.release());
		lastError = other.lastError;
	}

	ProjectPrivate::~ProjectPrivate()
	{
		close();
	}

	bool ProjectPrivate::save()
	{
		if (nullptr == file.get())
		{
			file.reset(new QFile(directory.absoluteFilePath("project.meega")));

			if (false == file->open(QIODevice::ReadWrite))
			{
				lastError = QObject::tr("Could not open or create project file.");

				file.reset(nullptr);
				return false;
			}
		}
		else
		{
			lastError = QObject::tr("No project file is open.");
		}

		file->resize(0);
		file->seek(0);

		QDataStream stream(file.get());
		stream << version << plugin->id() << plugin->name() << name;

		return true;
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

	bool ProjectPrivate::load(QDir dir)
	{
		if (nullptr != file.get())
		{
			lastError = QObject::tr("A project file is already open.");
			return false;
		}

		directory = dir;
		std::unique_ptr<QFile> openedFile(new QFile(directory.absoluteFilePath("project.meega")));

		if (false == openedFile->exists())
		{
			lastError = QObject::tr("A project file does not exist in the selected directory.");
			return false;
		}

		if (false == openedFile->open(QIODevice::ReadWrite))
		{
			lastError = QObject::tr("Could not open project file with write permissions.");
			return false;
		}

		QDataStream stream(openedFile.get());
		uint32_t inPluginId = PluginId::INVALID;
		QString inPluginName;

		stream >> version;
		if (version > 1)
		{
			version = 0;
			lastError = QObject::tr("The file was created with a newer version of the software.");

			return false;
		}

		stream >> inPluginId;
		
		Plugin* inPlugin = PluginManager::getPluginById(inPluginId);

		if (nullptr == inPlugin)
		{
			stream >> inPluginName;
			lastError = QObject::tr("The plugin %1 has not been loaded.").arg(inPluginName);

			return false;
		}
		
		if (Plugin::Type::Project != inPlugin->type())
		{
			lastError = QObject::tr("There is an error in the plugin specified by the file or the plugin is misidentified.");
			return false;
		}

		plugin = dynamic_cast<ProjectPlugin*>(inPlugin);
		stream >> name;

		file.reset(openedFile.release());
		return true;
	}

	QString ProjectPrivate::getLastError()
	{
		QString ret = lastError;
		lastError.clear();

		return ret;
	}
}