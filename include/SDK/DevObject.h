#ifndef _ENGINE_DEV_OBJECT_H_
#define _ENGINE_DEV_OBJECT_H_

#include "Config.h"

#include <QtWidgets/QWidget>

namespace MeegaSDK
{
	/**
	 * @brief
	 *  For development builds, the sub-classing DevObject provides facilities for the object
	 *  to integrate itself in the development tools at the cost of adding space
	 *  and processing overhead.
	 *
	 * @details
	 *  DevObject inherits QObject to simplify coding for pre-processor support if a sub-class
	 *  needs signal/slot functionality.  For non-developent builds, this class compiles down
	 *  to nothing.
	 */
	class MEEGA_SDK_CLASS DevObject : public QObject
	{
	public:
		DevObject();
		virtual ~DevObject();

		virtual QWidget* makePropertiesWidget();
	};
}

#endif // _ENGINE_DEV_OBJECT_H_