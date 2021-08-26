#include "broker_lock.h"

#include "lock.h"

namespace
{
	taste::Lock broker_lock;
}

extern "C"
{
	void Broker_acquire_lock()
	{
		broker_lock.lock();
	}

    void Broker_release_lock()
	{
		broker_lock.unlock();
	}
}
