#ifndef _CONCURRENT_PRODUCE_CONSUME_H_
#define _CONCURRENT_PRODUCE_CONSUME_H_

#include "Internal/ProducerInternal.h"

#include "Reference.h"

namespace Concurrent
{
	template<typename T>
	class Producer
	{
	public:
		Producer(const Producer<T>&) = delete;

		Producer(Producer&& other);
		Producer();

		virtual ~Producer();

		bool push(const T &item);
		bool push(T&& item);

		bool consume(T& out);
		bool tryConsume(T& out);

		bool isEmpty() const;

		void end();

		Reference< ProducerInternal<T> > mInternal;
	};

	///////////// Implmentation /////////////////

	/////////////////////////////////////////////
	template<typename T>
	Producer<T>::Producer(Producer<T>&& other)
		: mInternal(other.mInternal)
	{
		other.mInternal.makeNull();
	}

	template<typename T>
	Producer<T>::Producer()
	{
		mInternal = Reference< ProducerInternal<T> >::create();
		mInternal->endCalled.store(false);
	}

	template<typename T>
	Producer<T>::~Producer()
	{
		mInternal->end();
	}

	template<typename T>
	bool Producer<T>::push(const T &item)
	{
		if (mInternal->endCalled)
			return false;

		mInternal->pushMessage(item);
		return true;
	}

	template<typename T>
	bool Producer<T>::push(T&& item)
	{
		if (mInternal->endCalled)
			return false;

		mInternal->pushMessage(std::forward<T>(item));
		return true;
	}

	template<typename T>
	bool Producer<T>::consume(T& out)
	{
		Reference< ProducerInternal<T> > localInternal(mInternal);
		return localInternal->getMessage(out);
	}

	template<typename T>
	bool Producer<T>::tryConsume(T& out)
	{
		return mInternal->getMessage(out, true);
	}

	template<typename T>
	bool Producer<T>::isEmpty() const
	{
		return mInternal->messages.isEmpty();
	}

	template<typename T>
	void Producer<T>::end()
	{
		mInternal->end();
	}
}

#endif // _CONCURRENT_PRODUCE_CONSUME_H_
