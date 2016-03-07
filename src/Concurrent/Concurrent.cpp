#include <Concurrent/Concurrent.h>

#include <thread>

namespace Concurrent
{
	bool initialize()
	{
		return true;
	}

	void shutdown()
	{

	}

	unsigned int hardwareConcurrency()
	{
		return std::thread::hardware_concurrency();
	}
}