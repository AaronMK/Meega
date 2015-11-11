#ifndef _MEEGA_SDK_PROJECT_H_
#define _MEEGA_SDK_PROJECT_H_

#include "../Config.h"

#include <QtCore/QDir>

#include <memory>

namespace MeegaSDK
{
	class ProjectPrivate;

	/**
	 * @brief 
	 *  Common interface for navigating, saving and loading of project assets and settings.
	 *
	 *  While the actual methods of storage/retrieval of assets and supporting funtionality
	 *  will vary greatly based on the subclass, all projects are given a full sub-directory
	 *  to store files as they see fit.  
	 */
	class MEEGA_SDK_CLASS Project
	{
	public:
		Project(std::unique_ptr<ProjectPrivate>&& privParams);
		virtual ~Project();

		/**
		 * @brief
		 *   Saves the project.
		 *
		 *   This default implementation saves all base project data, and should be called in
		 *   any overrides.
		 */
		virtual bool save();

		/**
		 * @brief
		 *   Opens a project in the provided directory, returning a valid pointer on success.
		 */
		static std::unique_ptr<Project> openProject(QDir dir);

	protected:

		/**
		 * @brief
		 *   Obtains the directory for custom project data.
		 */
		QDir dataDir() const;

		/**
		 * @brief
		 *   Obtains the name of the project.
		 */
		QString name() const;

	private:
		std::unique_ptr<ProjectPrivate> mProjectPrivate;
	};
}

#endif // _MEEGA_SDK_PROJECT_H_