#ifndef _ENGINE_MUTEX_LOCKER_H_
#define _ENGINE_MUTEX_LOCKER_H_

#include "Mutex.h"

namespace Concurrent
{
	/**
	 * Scope based locking for a mutex.  The constructor will take give ownership of the Mutex to
	 * the current thread, and destructor will automatically release ownership.
	 */
	class CONCURRENT_DYNAMIC_CLASS MutexLocker
	{
	public:
		MutexLocker(const MutexLocker&) = delete;
		MutexLocker& operator=(const MutexLocker&) = delete;

		/**
		 * Contructs a locker that will take ownership of the passed Mutex.
		 */
		MutexLocker(Mutex* M);

		/**
		 * Destructor automatically releases ownership of Mutex.
		 */
		virtual ~MutexLocker();

	private:
		Mutex* theMutex;
	};
}

#endif // _ENGINE_MUTEX_LOCKER_H_