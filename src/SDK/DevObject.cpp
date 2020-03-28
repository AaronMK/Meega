#include <SDK/DevObject.h>

namespace MeegaSDK
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
