#include <AppsCommon/AppsCommon.h>

#include <QtCore/QFile>

namespace AppsCommon
{
	QString fileToString(const QString &path)
	{
		QFile file(path);

		if (file.open(QIODevice::ReadOnly | QIODevice::Text))
			return QString(file.readAll());

		return QString();
	}
}