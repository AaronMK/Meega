#ifndef _ENGINE_DEV_OBJECT_H_
#define _ENGINE_DEV_OBJECT_H_

#include "DevSupport.h"

#ifdef ENGINE_DEVEOPMENT_SUPPORT

#include <QtWidgets/QWidget>

namespace Engine
{
	/**
	 * For development builds, the sub-classing DevObject provides facilities for the object
	 * to integrate itself in the development tools at the cost of adding space
	 * and processing overhead.
	 *
	 * DevObject inherits QObject to simplify coding for pre-processor support if a sub-class
	 * needs signal/slot functionality.  For non-developent builds, this class compiles down
	 * to nothing.
	 */
	class ENGINE_DYNAMIC_CLASS DevObject : public QObject
	{
	public:
		DevObject();
		virtual ~DevObject();

		virtual QWidget* makePropertiesWidget();
	};
}

#else

namespace Engine
{
	class DevObject 
	{
	};
}

#endif // ENGINE_DEVEOPMENT_SUPPORT

#endif // _ENGINE_DEV_OBJECT_H_