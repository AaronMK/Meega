#ifndef _CONCURRENT_REFERENCE_H_
#define _CONCURRENT_REFERENCE_H_

#include "Internal/RefBase.h"

namespace Concurrent
{
	template<typename T>
	class WeakRef;

	/**
	 * @brief
	 *  Holds a reference counted pointer to an object.
	 * 
	 *  Operators make this act like normal pointers.  get() can be used to obtain the actual pointer.
	 *  It wraps an implementation that is thread-safe for all provided functionality
	 *  of the Reference objects.
	 */
	template<typename T>
	class Reference : public RefBase<T>
	{
		template<typename U>
		friend class Reference;

	public:

		/**
		 * @brief
		 *  Creates a new reference counted item of type T with the supplied arguments
		 *  and its reference counting functionality in a single allocation.  Use this to
		 *  reduce memory fragmentation.
		 */
		template <typename... Args>
		static Reference<T> create(Args&& ...arguments);

		/**
		 * @brief
		 *  Creates a reference to the passed object.  The object will now be managed by
		 *  the reference counting system.
		 */
		Reference(T* item = nullptr);

		/**
		 * @brief
		 *  Creates a reference to the same object the referenced by Other, and increments
		 *  the reference count.
		 */
		Reference(const Reference<T> &Other);

		/**
		 * @brief
		 *  Creates a strong reference from a weak one.
		 */
		Reference(const WeakRef<T> &Other);

		/**
		 * @brief
		 *  Creates a reference to the same object the referenced by Other, and increments
		 *  the reference count.  Implmentation will ensure pointer compatibility, generating
		 *  a compile error on incompatible pointers.
		 */
		template<typename U>
		Reference(const Reference<U> &Other);

		/**
		 * @brief
		 *  Decrements reference count of tracked object, deleting it if the count goes
		 *  to zero.
		 */
		virtual ~Reference();

		/**
		 * @brief
		 *  Acts like the set operator of a normal pointer, but handles reference
		 *  counting in the background.  Template logic produces a compiler error
		 *  if pointer types are not compatible.
		 */
		template<typename U>
		Reference<T>& operator=(const Reference<U> &Other);

		/**
		 * @brief
		 *  Acts like the set operator of a normal pointer, but handles reference
		 *  counting in the background.
		 */
		Reference<T>& operator=(const Reference<T> &Other);

		/**
		 * @brief
		 *  "de-reference" operator acts as if the Reference were a normal pointer.
		 */
		T& operator*();

		/**
		 * @brief
		 *  "de-reference" operator acts as if the Reference were a normal pointer.
		 */
		const T& operator*() const;

		/**
		 * @brief
		 *  "Member" operator acts as if the Reference were a normal pointer.
		 */
		T* operator->();

		/**
		 * @brief
		 *  "Member" operator acts as if the Reference were a normal pointer.
		 */
		const T* operator->() const;

		/**
		 * @brief
		 *  Obtains a raw pointer to the managed object.
		 */
		T* get();

		/**
		 * @brief
		 *  Obtains a raw const pointer to the managed object.
		 */
		const T* get() const;

		/**
		 * @brief
		 *  References are equal if this and Other reference the same object.
		 */
		template<typename U>
		bool operator==(Reference<U> &Other);

		/**
		 * @brief
		 *  References are equal if this and Other reference the same object.
		 */
		bool operator==(Reference<T> &Other);

		/**
		 * @brief
		 *  Comparison operator to make Reference compatible with sorting containers.
		 */
		template<typename U>
		bool operator<(Reference<U> &Other);

		/**
		 * @brief
		 *  Comparison operator to make Reference compatible with sorting containers.
		 */
		bool operator<(Reference<T> &Other);

		/*
		 * @brief
		 *  Acts like a dynamic cast of pointers, but creates a reference instead.
		 */
		template<typename U>
		static Reference<T> dynamicCast(const Reference<U> &Ref);

		/**
		 * @brief
		 *  Makes the reference object nullptr, decrements the count of the previously referenced
		 *  object, and deletes it if the count is zero.
		 */
		void makeNull();

		/**
		 * @brief
		 *  Returns true if the reference is null.
		 */
		bool isNull() const;
		
		/**
		 * @brief
		 *  Just like a normal pointer, true if the reference is not nullptr.
		 */
		operator bool() const;

		/**
		 * @brief
		 *  Returns the number of references to the managed object.
		 */
		long use_count() const;
	};

	/**
	 * @brief
	 *  Creates a weak reference.
	 * 
	 *  lock() can be used to get a strong reference that will either
	 *  be nullptr if the object has been destroyed, or can be used to prevent destruction and for
	 *  access to the object.
	 */
	template<typename T>
	class WeakRef : public WeakRefBase<T>
	{
	public:
		WeakRef(const WeakRef<T> &other);
		WeakRef(const Reference<T> &other);

		/**
		 * @brief
		 *  Creates a strong reference that will prevent destruction of the referenced object
		 *  if it still exists, or returns a nullptr reference if it has been destryed.
		 */
		Reference<T> lock() const;
	};

	///////////////////////////////////////////////////////////////////////

	template<typename T>
	RefBase<T>::RefBase()
	{
	}

	template<typename T>
	RefBase<T>::RefBase(const std::shared_ptr<T> &ptr)
	{
		std::atomic_exchange<T>(&mPtr, ptr);
	}

	template<typename T>
	RefBase<T>::~RefBase()
	{
	}

	////////////////////////////////

	template<typename T>
	template <typename... Args>
	Reference<T> Reference<T>::create(Args&& ...arguments)
	{
		Reference<T> ret;
		ret.mPtr = std::make_shared<T>(arguments...);

		return ret;
	}

	template<typename T>
	Reference<T>::Reference(T* item)
		: RefBase(std::shared_ptr<T>(item))
	{
	}

	template<typename T>
	Reference<T>::Reference(const Reference<T> &Other)
		: RefBase(Other.mPtr)
	{
	}

	template<typename T>
	Reference<T>::Reference(const WeakRef<T> &Other)
		: RefBase(Other.mWeakPtr.lock())
	{
	}

	template<typename T>
	template<typename U>
	Reference<T>::Reference(const Reference<U> &Other)
	{
		static_assert(std::is_base_of<T, U>::value, "References are not of dynamic types.");

		Reference<U> uRef;
		std::atomic_exchange<U>(&uRef.mPtr, Other.mPtr);
		mPtr = std::dynamic_pointer_cast<T>(uRef.mPtr);
	}

	template<typename T>
	Reference<T>::~Reference()
	{
		// base destructor decrements and possibly deletes counter.
	}

	template<typename T>
	template<typename U>
	Reference<T>& Reference<T>::operator=(const Reference<U> &Other)
	{
		static_assert(std::is_base_of<T, U>::value, "References are not of dynamic types.");
		
		Reference<U> uRef;
		std::atomic_exchange<U>(&uRef.mPtr, Other.mPtr);
		mPtr = std::dynamic_pointer_cast<T>(uRef.mPtr);

		return *this;
	}

	template<typename T>
	Reference<T>& Reference<T>::operator=(const Reference<T> &Other)
	{
		std::atomic_exchange<T>(&mPtr, Other.mPtr);
		return *this;
	}

	template<typename T>
	T& Reference<T>::operator*()
	{
		return *mPtr;
	}

	template<typename T>
	const T& Reference<T>::operator*() const
	{
		return *mPtr;
	}

	template<typename T>
	T* Reference<T>::operator->()
	{
		return mPtr.get();
	}

	template<typename T>
	const T* Reference<T>::operator->() const
	{
		return mPtr.get();
	}

	template<typename T>
	T* Reference<T>::get()
	{
		return mPtr.get();
	}

	template<typename T>
	const T* Reference<T>::get() const
	{
		return mPtr.get();
	}

	template<typename T>
	template<typename U>
	bool Reference<T>::operator==(Reference<U> &Other)
	{
		return (mPtr == Reference<T>(Other).mPtr);
	}

	template<typename T>
	bool Reference<T>::operator==(Reference<T> &Other)
	{
		return (mPtr == Other.mPtr);
	}

	template<typename T>
	template<typename U>
	bool Reference<T>::operator<(Reference<U> &Other)
	{
		return (mPtr < Reference<T>(Other).mPtr);
	}

	template<typename T>
	bool Reference<T>::operator<(Reference<T> &Other)
	{
		return mPtr < Other.mPtr;
	}

	template<typename T>
	template<typename U>
	static Reference<T> Reference<T>::dynamicCast(const Reference<U> &Ref)
	{
		static_assert(std::is_base_of<T, U>::value || std::is_base_of<U, T>::value, "References are not of dynamic types.");

		Reference<T> ret;
		ret.mPtr = std::dynamic_pointer_cast<U>(Ref.mPtr);

		return ret;
	}

	template<typename T>
	void Reference<T>::makeNull()
	{
		mPtr.reset();
	}

	template<typename T>
	bool Reference<T>::isNull() const
	{
		return !((bool)mPtr);
	}

	template<typename T>
	Reference<T>::operator bool() const
	{
		return (bool)mPtr;
	}

	template<typename T>
	long Reference<T>::use_count() const
	{
		return mPtr.use_count()
	}

	///////////////////////////////////////////////////////

	template<typename T>
	WeakRefBase<T>::WeakRefBase()
	{
	}

	template<typename T>
	WeakRefBase<T>::WeakRefBase(const std::weak_ptr<T> &ptr)
		: mWeakPtr(ptr)
	{
	}

	template<typename T>
	WeakRefBase<T>::WeakRefBase(const std::shared_ptr<T> &ptr)
		: mWeakPtr(ptr)
	{
	}

	template<typename T>
	WeakRefBase<T>::~WeakRefBase()
	{
	}

	/////////////////////////////////////

	template<typename T>
	WeakRef<T>::WeakRef(const WeakRef<T> &other)
		: WeakRefBase(other.mWeakPtr)
	{
	}

	template<typename T>
	WeakRef<T>::WeakRef(const Reference<T> &other)
		: WeakRefBase(other.mPtr)
	{
	}

	template<typename T>
	Reference<T> WeakRef<T>::lock() const
	{
		return Reference<T>(*this);
	}
}

#endif // _CONCURRENT_REFERENCE_H_