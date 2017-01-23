#include <Engine/DevSupport/DevSupport.h>

#include <Engine/DevSupport/QGuiThreadQueue.qt.h>

namespace Engine
{
	void setGuiThread(QThread* thread)
	{
		QGuiThreadQueue::setGuiThread(thread);
	}
}