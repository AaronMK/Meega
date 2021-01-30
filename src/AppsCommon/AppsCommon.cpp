#include <AppsCommon/AppsCommon.h>

#include <QtCore/QFile>

#include <QtWidgets/QApplication>
#include <QtWidgets/QStyle>


#if defined(_WIN32)
#	if defined(_DEBUG)
#		pragma comment(lib, "Qt6Cored.lib")
#		pragma comment(lib, "Qt6Widgetsd.lib")
#	else
#		pragma comment(lib, "Qt6Core.lib")
#		pragma comment(lib, "Qt6Widgets.lib")
#	endif
#endif

namespace AppsCommon
{
	QString fileToString(const QString &path)
	{
		QFile file(path);

		if (file.open(QIODevice::ReadOnly | QIODevice::Text))
			return QString(file.readAll());

		return QString();
	}

	QString getStyleSheet()
	{
		return fileToString(":/Styles/MasterStyle.txt");
	}
}