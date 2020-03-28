#ifndef _ENGINE_Q_GUI_THREAD_QUEUE_H_
#define _ENGINE_Q_GUI_THREAD_QUEUE_H_

#include <QtCore/QObject>
#include <QtCore/QThread>

#include <functional>

namespace Engine
{
	class QGuiThreadQueue : public QObject
	{
		Q_OBJECT
	public:
		static void setGuiThread(QThread* thread);
		static void enqueue(std::function<void()>&& func);

	private:
		static QGuiThreadQueue* instance();

		QGuiThreadQueue();
		virtual ~QGuiThreadQueue();

		void runItem();

	signals:
		void itemReady();
	};
}

#endif // _ENGINE_Q_GUI_THREAD_QUEUE_H_