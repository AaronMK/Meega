#include <SDK/DevSupport.h>

#include <SDK/QGuiThreadQueue.qt.h>

namespace Engine
{
	void setGuiThread(QThread* thread)
	{
		QGuiThreadQueue::setGuiThread(thread);
	}
}