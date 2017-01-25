#ifndef _ALIGN_16_H_
#define _ALIGN_16_H_

#include "../Config.h"

#include <memory>

#ifdef __GNUC__
#	define ALIGN_16_PRE
#	define ALIGN_16_POST __attribute__((aligned (16)))
#elif _WIN32
#	define ALIGN_16_PRE __declspec(align(16))
#	define ALIGN_16_POST ENGINE_EXPORT
#endif

#ifndef __SSE__
#	define __SSE__
#endif

#ifndef __MMX__
#	define __MMX__
#endif

#include <xmmintrin.h>
#include <assert.h>

namespace Engine
{
	/**
	 * @brief
	 *  Any derived class will be aligned on 16 byte boundaries.  If a class has a member requiring
	 *  16 byte alignment, it must also derive this class.
	 */
	ALIGN_16_PRE class ALIGN_16_POST Align16
	{
	public:
		void* operator new(size_t Size);
		void* operator new(size_t Size, void* Addr);
		void operator delete(void* Ptr, size_t Size);
		void operator delete(void* Ptr, void* Addr);
		void* operator new[](size_t Size);
		void operator delete[](void* Ptr);
	};
}
////////////////// Implementation //////////////////

#endif // _ALIGN_16_H_