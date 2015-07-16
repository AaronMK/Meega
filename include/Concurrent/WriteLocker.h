#ifndef _CONCURRENT_WRITE_LOCKER_H_
#define _CONCURRENT_WRITE_LOCKER_H_

#include <Concurrent/RWLock.h>

namespace Concurrent
{
	/**
	 * Class for scope based write locking of an RWLock.
	 */
	class CONCURRENT_DYNAMIC_CLASS WriteLocker
	{
	public:
		WriteLocker(const WriteLocker&) = delete;
		WriteLocker& operator=(const WriteLocker&) = delete;

		/**
		 * Acquires the passed lock for writing, blocking until it has ownership.
		 */
		WriteLocker(RWLock *lock);
		
		/**
		 * Releases ownership of the lock.
		 */
		virtual ~WriteLocker();

	private:
		RWLock* m_lock;
	};
}

#endif // _CONCURRENT_WRITE_LOCKER_H_