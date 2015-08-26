#include "../private_include/DevSupport/DevObjectManager.h"

#ifdef ENGINE_DEVEOPMENT_SUPPORT

#include <Engine/DevSupport/DevObject.h>

#include <QtGui/QStandardItem>
#include <QtGui/QStandardItemModel>

#include <functional>

namespace Engine
{
	static QStandardItemModel DevObjectModel;

	///////////////////////////////////

	static void onObjDestroyed(QDevObjectItem* obj)
	{
		QStandardItem* parentItem = obj->QStandardItem::parent();

		if (parentItem)
			parentItem->removeRow(obj->row());
		else
			delete obj;
	}

	QDevObjectItem::QDevObjectItem(DevObject* obj)
	{
		mObj = obj;
		setText(mObj->objectName());

		connect(mObj, &QObject::objectNameChanged, this, &QDevObjectItem::onObjectRenamed);
		connect(mObj, &QObject::destroyed, std::bind(&onObjDestroyed, this));
	}

	QDevObjectItem::~QDevObjectItem()
	{

	}

	void onObjectDetroyed();
	void QDevObjectItem::onObjectRenamed(const QString &objectName)
	{
		setText(mObj->objectName());
	}

	///////////////////////////////////

	namespace DevObjectManager
	{
		bool registerObject(DevObject* obj)
		{
			QDevObjectItem* item = new QDevObjectItem(obj);

			DevObjectModel.appendRow(item);

			return true;
		}
	}
}

#endif // ENGINE_DEVEOPMENT_SUPPORT