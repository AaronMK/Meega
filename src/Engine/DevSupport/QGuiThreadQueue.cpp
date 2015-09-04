#include "../private_include/DevSupport/QGuiThreadQueue.qt.h"

#include <Concurrent/Producer.h>

#include <QtWidgets/QApplication>

using namespace Concurrent;

namespace Engine
{
	static Producer<std::function<void()>> taskQueue;

	void QGuiThreadQueue::setGuiThread(QThread* thread)
	{
		instance()->moveToThread(thread);
	}

	void QGuiThreadQueue::enqueue(std::function<void()>&& func)
	{
		taskQueue.push(std::forward<std::function<void()>>(func));
		emit instance()->itemReady();
	}

	QGuiThreadQueue* QGuiThreadQueue::instance()
	{
		static QGuiThreadQueue inst;
		return &inst;
	}

	QGuiThreadQueue::QGuiThreadQueue()
	{
		moveToThread(qApp->thread());
		connect(this, &QGuiThreadQueue::itemReady, &QGuiThreadQueue::runItem);
	}

	QGuiThreadQueue::~QGuiThreadQueue()
	{

	}

	void QGuiThreadQueue::runItem()
	{
		std::function<void()> func;

		if (taskQueue.consume(func))
			func();
	}
}