#include <Engine/DevSupport/DevSupport.h>

#include "../private_include/DevSupport/QGuiThreadQueue.qt.h"

namespace Engine
{
	void setGuiThread(QThread* thread)
	{
		QGuiThreadQueue::setGuiThread(thread);
	}
}