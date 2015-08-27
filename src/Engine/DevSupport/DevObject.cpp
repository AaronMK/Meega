#include <Engine/DevSupport/DevObject.h>

#ifdef ENGINE_DEVEOPMENT_SUPPORT

#include "../private_include/DevSupport/DevObjectManager.h"

namespace Engine
{
	DevObject::DevObject()
	{
		setObjectName(QString(tr("<untitled>")));
	}

	DevObject::~DevObject()
	{

	}

	QWidget* DevObject::makePropertiesWidget()
	{
		return nullptr;
	}
}

#endif // ENGINE_DEVEOPMENT_SUPPORT