#ifndef _CONCURRENT_CONDITION_H_
#define _CONCURRENT_CONDITION_H_

#include "Config.h"

#include "Internal/ConditionPlatform.h"

namespace Concurrent
{	
	/**
	 * Abstracts a manual-reset condtion that is cooperative with the system thread
	 * pool.
	 */
	class CONCURRENT_DYNAMIC_CLASS Condition : public ConditionPlatform
	{
	public:

		/**
		 * Constructor creates a condition that is not triggered.
		 */
		Condition();
		
		/**
		 * Detroys the condition, and returns false from any wait() calls.
		 */
		virtual ~Condition();
		
		/**
		 * Blocks until the condition is triggered or detroyed.  Returns true
		 * if the condition was triggered, and false if it was destroyed.
		 */
		bool wait();
		
		/**
		 * Triggers the condition, and releases and returns from all wait calls.  Any subsequent
		 * threads that call wait() will return until reset() is called.
		 */
		void trigger();

		/**
		 * Returns true if in the triggered state, ie if wait() would immediately return.
		 */
		bool isTriggered() const;
		
		/**
		 * Resets the condition.
		 */
		void reset();
	};
}

#endif // _CONCURRENT_CONDITION_H_