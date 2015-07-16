#include <Engine/Memory/Arena.h>

#include <malloc.h>

namespace Engine
{
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

	////////////////////////////////

	Arena::EntryBase::EntryBase()
	{
		mNext = nullptr;
	}
	
	Arena::EntryBase::~EntryBase()
	{

	}
}