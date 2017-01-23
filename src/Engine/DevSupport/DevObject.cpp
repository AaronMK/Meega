#include <Engine/DevSupport/DevObject.h>

#ifdef ENGINE_DEVELOPMENT_SUPPORT

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

#endif // ENGINE_DEVELOPMENT_SUPPORT
