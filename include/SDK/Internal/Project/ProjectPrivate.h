#ifndef _MEEGA_SDK_PROJECT_PRIVATE_H_
#define _MEEGA_SDK_PROJECT_PRIVATE_H_

#include "../../Config.h"

#include <SDK/Plugins/ProjectPlugin.h>

#include <QtCore/QDir>
#include <QtCore/QFile>

#include <memory>

namespace MeegaSDK
{
	class ProjectPlugin;

	/**
	 * @internal
	 *
	 * @brief
	 *   Handles all internal functionality of Project that is not exposed
	 *   through the SDK.
	 */
	class MEEGA_SDK_CLASS ProjectPrivate final
	{
	public:
		ProjectPrivate(const ProjectPrivate&) = delete;

		/**
		 * @brief
		 *   Creates and invalid ProjectPrivate object.
		 */
		ProjectPrivate();

		/**
		 * @brief
		 *   Move constructor.
		 *
		 *   Object passed to the constructor will be invalid upon return,
		 *   and the contructed object will have the same current state as
		 *   the passed object.
		 */
		ProjectPrivate(ProjectPrivate&& other);
		
		/**
		 * @brief
		 *   Closes, but does not automatically save the project file.
		 */
		~ProjectPrivate();

		/**
		 * @brief
		 *   Saves the project file to disk.
		 *
		 *   This will always save with the most current supported version.  The project
		 *   file will be created if it does not exist, and overwritten if it does.
		 */
		bool save();

		/*
		 * @brief
		 *	 Closes the project file and resets the object to an invalid state.
		 */
		void close();

		bool load(QDir dir);

		QString getLastError();

		QDir directory;
		QString name;

		ProjectPlugin* plugin;
		uint32_t version;

		std::unique_ptr<QFile> file;
		QString lastError;
	};
}

#endif // _MEEGA_SDK_PROJECT_PRIVATE_H_