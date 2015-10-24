#ifndef _MEEGA_SDK_PROJECT_PRIVATE_H_
#define _MEEGA_SDK_PROJECT_PRIVATE_H_

#include "../../Config.h"

#include <QtCore/QDir>

namespace MeegaSDK
{
	class MEEGA_SDK_CLASS ProjectPrivate
	{
	public:
		QDir projectDir;
		QString projectName;
	};
}

#endif // _MEEGA_SDK_PROJECT_PRIVATE_H_