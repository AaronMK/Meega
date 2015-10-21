#ifndef _MEEGA_SDK_PROJECT_PROJECT_H_
#define _MEEGA_SDK_PROJECT_PROJECT_H_

#include "../Plugins/Plugin.h"
#include "../Project/Project.h"

#include <QtCore/QDir>

#include <memory>

namespace MeegaSDK
{
	class ProjectPrivate;
	
	/**
	 * @brief
	 *   Class for plugins that implement project factory functionality.
	 */
	class MEEGA_SDK_CLASS ProjectPlugin : public Plugin
	{
	public:
		ProjectPlugin();
		virtual ~ProjectPlugin();

		virtual uint32_t id() override = 0;
		virtual Type type() override final;

		/**
		 * Called after the corresponding project type and a root directory has been selected in the
		 * New Project dialog.  The implementation will get additional information from the user as
		 * needed, and return a newly created project.
		 *
		 * @param data
		 *   This parameter is passed directly to the Project constructor.  It contains internal data
		 *   and initialization enabling base Project functions to be usable during subclass construction.
		 */
		virtual std::unique_ptr<Project> createProject(std::unique_ptr<ProjectPrivate>&& data) = 0;
		
		/**
		 * Called after a project directory has been selected to open an existing project. 
		 *
		 * @param data
		 *   This parameter is passed directly to the Project constructor.  It contains internal data
		 *   and initialization enabling base Project functions to be usable during subclass construction.
		 */
		virtual std::unique_ptr<Project> openProject(std::unique_ptr<ProjectPrivate>&& data) = 0;

		/**
		 * The name used for project type selection.
		 */
		virtual QString name() = 0;

		/**
		 * Gets a user friendly description of the project type.
		 */
		virtual QString description() = 0;
	};
}

#endif // _MEEGA_SDK_PROJECT_PROJECT_H_