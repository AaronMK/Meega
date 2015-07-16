#ifndef _ENGINE_ARENA_H_
#define _ENGINE_ARENA_H_

#include <Engine/Config.h>

#include <atomic>
#include <memory>

#include <malloc.h>

namespace Engine
{
	class Arena
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
		Arena(const Arena &other) = delete;

		Arena(size_t byteSize);
		Arena(Arena&& other);

		virtual ~Arena();

		template<typename T, typename... Args>
		T* Push(Args&& ...args);

		template<typename T, typename... Args>
		T* PushAligned(size_t alignment, Args&& ...args);

		/**
		 * Destroys all objects in the Arena and freeing all the
		 * space.  Any pointers returned by the push functions
		 * become invalid.
		 */
		void clear();

		Arena& operator=(const Arena &other) = delete;
		Arena& operator=(Arena&& other);

	private:
		void* mMemory;
		void* mStackMarker;

		size_t mAllocSize;
		size_t mRemainingSpace;

		EntryBase* mLastAdded;
		EntryBase* mFirstAdded;
	};

	/////////////////////////////////////////////

	Arena::Arena(size_t byteSize)
	{
		mMemory = (unsigned char*)_aligned_malloc(16, mAllocSize);
		mStackMarker = mMemory;

		mAllocSize = byteSize;
		mRemainingSpace = mAllocSize;

		mLastAdded = nullptr;
		mFirstAdded = nullptr;
	}

	Arena::Arena(Arena&& other)
	{
		mMemory = other.mMemory;
		mStackMarker = other.mStackMarker;

		mAllocSize = other.mAllocSize;
		mRemainingSpace = other.mRemainingSpace;

		mLastAdded = other.mLastAdded;
		mFirstAdded = other.mFirstAdded;

		other.mMemory = nullptr;
	}

	Arena::~Arena()
	{
		clear();
		_aligned_free(mMemory);
	}

	template <typename T, typename... Args>
	T* Arena::Push(Args&& ...args)
	{
		return PushAligned<T>(0, args...);
	}

	template<typename T, typename... Args>
	T* Arena::PushAligned(size_t alignment, Args&& ...args)
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

	void Arena::clear()
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

	Arena& Arena::operator=(Arena&& other)
	{
		mMemory = other.mMemory;
		mStackMarker = other.mStackMarker;

		mAllocSize = other.mAllocSize;
		mRemainingSpace = other.mRemainingSpace;

		mLastAdded = other.mLastAdded;
		mFirstAdded = other.mFirstAdded;

		other.mMemory = nullptr;

		return *this;
	}

	//////////////////////////////////////////////

	Arena::EntryBase::EntryBase()
	{
		mNext = nullptr;
	}

	Arena::EntryBase::~EntryBase()
	{

	}

	//////////////////////////////////////////////

	template<typename T>
	template<typename... Args>
	Arena::Entry<T>::Entry(Args&& ...args)
		: EntryBase(), mItem(args...)
	{
	}

	template<typename T>
	Arena::Entry<T>::~Entry()
	{
	}
}

#endif // _ENGINE_ARENA_H_