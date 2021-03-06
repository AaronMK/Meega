#ifndef _ENGINE_ALIGNED_ALLOCATOR_H_
#define _ENGINE_ALIGNED_ALLOCATOR_H_

#include "../Config.h"

#include <cstdlib>

namespace Engine
{
	/**
	 * @brief
	 *  Allocator that can be used as a type parameter to STL collection classes
	 *  to guarentee proper alignment for items.
	 */
	template<typename T>
	class AlignedAllocator
	{
	public:
		typedef T value_type;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;

		template<typename U>
		struct rebind
		{
			typedef AlignedAllocator<U> other;
		};

		AlignedAllocator()
		{
		}

		~AlignedAllocator()
		{
		}

		AlignedAllocator(AlignedAllocator const&)
		{
		}

		template<typename U>
		AlignedAllocator(AlignedAllocator<U> const&)
		{
		}

		pointer address(reference r)
		{
			return &r;
		}

		const_pointer address(const_reference r)
		{
			return &r;
		}

		pointer allocate(size_type cnt, typename std::allocator<void>::const_pointer = 0)
		{
			return reinterpret_cast<pointer>(aligned_alloc(cnt * sizeof(T), alignof(T)));
		}

		void deallocate(pointer p, size_type)
		{ 
			free(p);
		}

		size_type max_size() const
		{ 
			return std::numeric_limits<size_type>::max() / sizeof(T);
		}

		void construct(pointer p, const T& t)
		{
			new(p) T(t);
		}

		void destroy(pointer p)
		{
			p->~T();
		}

		bool operator==(AlignedAllocator const&)
		{
			return true;
		}

		bool operator!=(AlignedAllocator const& a)
		{
			return !operator==(a);
		}
	};
}

#endif // _ENGINE_ALIGNED_ALLOCATOR_H_