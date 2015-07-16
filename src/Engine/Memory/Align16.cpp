#include <Engine/Memory/Align16.h>

namespace Engine
{
	void* Align16::operator new(size_t Size)
	{
		return _mm_malloc(Size, 16);
	}

	void* Align16::operator new(size_t Size, void* Addr)
	{
		return Addr;
	}

	void Align16::operator delete(void* Ptr, size_t Size)
	{
		_mm_free(Ptr);
	}

	void Align16::operator delete(void* Ptr, void* Addr)
	{
		// This should never be called.  It is here to make compiler happy.
		assert(false);
	}

	void* Align16::operator new[](size_t Size)
	{
		return _mm_malloc(Size, 16);
	}

	void Align16::operator delete[] (void* Ptr)
	{
		_mm_free(Ptr);
	}
}