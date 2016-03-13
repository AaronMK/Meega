#ifndef _ENGINE_MEMORY_POOL_H_
#define _ENGINE_MEMORY_POOL_H_

#include "../../Config.h"

#include <atomic>
#include <memory>

#include <malloc.h>

namespace Engine
{
	class MemoryPool
	{
	private:
		class EntryBase
		{
		public:
			EntryBase();
			virtual ~EntryBase();

			EntryBase* mNext;
		};

		template<typename T>
		class Entry : public EntryBase
		{
		public:
			template<typename... Args>
			Entry(Args&& ...args);
			
			virtual ~Entry();

			T mItem;
		};

	public:
		MemoryPool(const MemoryPool &other) = delete;

		MemoryPool(size_t byteSize);
		MemoryPool(MemoryPool&& other);

		virtual ~MemoryPool();

		template<typename T, typename... Args>
		T* push(Args&& ...args);

		template<typename T, typename... Args>
		T* pushAligned(size_t alignment, Args&& ...args);

		/**
		 * @brief
		 *  Destroys all objects in the MemoryPool and freeing all the
		 *  space.  Any pointers returned by the push functions
		 *  become invalid.
		 */
		void clear();

		MemoryPool& operator=(const MemoryPool &other) = delete;
		MemoryPool& operator=(MemoryPool&& other);

	private:
		void* mMemory;
		void* mStackMarker;

		size_t mAllocSize;
		size_t mRemainingSpace;

		EntryBase* mLastAdded;
		EntryBase* mFirstAdded;
	};

	/////////////////////////////////////////////

	MemoryPool::MemoryPool(size_t byteSize)
	{
		mAllocSize = byteSize;
		mRemainingSpace = mAllocSize;

		mMemory = malloc(mAllocSize);
		mStackMarker = mMemory;

		mLastAdded = nullptr;
		mFirstAdded = nullptr;
	}

	MemoryPool::MemoryPool(MemoryPool&& other)
	{
		mAllocSize = other.mAllocSize;
		mRemainingSpace = other.mRemainingSpace;

		mMemory = other.mMemory;
		mStackMarker = other.mStackMarker;

		mLastAdded = other.mLastAdded;
		mFirstAdded = other.mFirstAdded;

		other.mMemory = nullptr;
	}

	MemoryPool::~MemoryPool()
	{
		clear();
		free(mMemory);
	}

	template <typename T, typename... Args>
	T* MemoryPool::push(Args&& ...args)
	{
		return pushAligned<T>(0, args...);
	}

	template<typename T, typename... Args>
	T* MemoryPool::pushAligned(size_t alignment, Args&& ...args)
	{
		if (nullptr == mMemory)
			return nullptr;

		alignment = (alignment < 4) ? 4 : alignment;

		void* alignResult = std::align(alignment, sizeof(Entry<T>),
		                               mStackMarker, mRemainingSpace);

		if (alignResult)
		{
			Entry<T>* entry = new (alignResult)Entry<T>(args...);

			if (nullptr == mFirstAdded)
				mFirstAdded = entry;

			if (mLastAdded)
				mLastAdded->mNext = entry;

			mLastAdded = entry;
			mStackMarker = (char*)mStackMarker + sizeof(Entry<T>);
			mRemainingSpace -= sizeof(Entry<T>);

			return &entry->mItem;
		}

		return nullptr;
	}

	void MemoryPool::clear()
	{
		if (nullptr == mMemory)
			return;

		EntryBase* entryPtr = mFirstAdded;
		while (entryPtr)
		{
			EntryBase* nextPtr = entryPtr->mNext;

			entryPtr->~EntryBase();
			entryPtr = nextPtr;
		}

		mStackMarker = mMemory;
		mRemainingSpace = mAllocSize;
		mLastAdded = nullptr;
		mFirstAdded = nullptr;
	}

	MemoryPool& MemoryPool::operator=(MemoryPool&& other)
	{
		if (mMemory)
		{
			clear();
			free(mMemory);
		}

		mAllocSize = other.mAllocSize;
		mRemainingSpace = other.mRemainingSpace;

		mMemory = other.mMemory;
		mStackMarker = other.mStackMarker;

		mLastAdded = other.mLastAdded;
		mFirstAdded = other.mFirstAdded;

		other.mMemory = nullptr;

		return *this;
	}

	//////////////////////////////////////////////

	MemoryPool::EntryBase::EntryBase()
	{
		mNext = nullptr;
	}

	MemoryPool::EntryBase::~EntryBase()
	{

	}

	//////////////////////////////////////////////

	template<typename T>
	template<typename... Args>
	MemoryPool::Entry<T>::Entry(Args&& ...args)
		: EntryBase(), mItem(args...)
	{
	}

	template<typename T>
	MemoryPool::Entry<T>::~Entry()
	{
	}
}

#endif // _ENGINE_MEMORY_POOL_H_