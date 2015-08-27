#ifndef _APPS_COMMON_H_
#define _APPS_COMMON_H_

#include <AppsCommon/Config.h>

#include <QtCore/QString>

namespace AppsCommon
{
	APPS_COMMON_FUNC_EXPORT QString fileToString(const QString &path);
	APPS_COMMON_FUNC_EXPORT QString getStyleSheet();
}

#endif // _APPS_COMMON_H_