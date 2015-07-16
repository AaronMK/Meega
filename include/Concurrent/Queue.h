#ifndef _CONCURRENT_QUEUE_H_
#define _CONCURRENT_QUEUE_H_

#include <Concurrent/Config.h>

#include <Concurrent/Internal/QueuePlatform.h>

namespace Concurrent
{
	/**
	 * Queue with a lock-free implementation on supported platforms.
	 */
	template<typename T>
	class Queue : public QueuePlatform<T>
	{
	public:

		/**
		 * Creates an empty queue.
		 */
		Queue();

		virtual ~Queue();

		/**
		 * Pushes an item onto the Queue.
		 */
		void push(const T& item);

		/**
		 * Pushes an item onto the Queue.
		 */
		void push(T&& item);

		/**
		 * Attempts to pop an item from the Queue, if there is something to
		 * de-queue, it is placed in destination and true is returned.
		 * Otherwise, destination remains unchanged and false is returned.
		 */
		bool tryPop(T& destination);

		/**
		 * Inspector to determine if the queue is empty.
		 */
		bool isEmpty() const;
	};

#ifdef _WIN32

	template<typename T>
	Queue<T>::Queue()
	{
	}

	template<typename T>
	Queue<T>::~Queue()
	{
	}

	template<typename T>
	void Queue<T>::push(const T& item)
	{
		mSysQueue.push(item);
	}

	template<typename T>
	void Queue<T>::push(T&& item)
	{
		mSysQueue.push(std::forward<T>(item));
	}

	template<typename T>
	bool Queue<T>::tryPop(T& destination)
	{
		return mSysQueue.try_pop(destination);
	}

	template<typename T>
	bool Queue<T>::isEmpty() const
	{
		return mSysQueue.empty();
	}

#endif
}

#endif _CONCURRENT_QUEUE_H_