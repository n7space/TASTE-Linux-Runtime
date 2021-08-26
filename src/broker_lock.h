#ifndef BROKER_LOCK_H
#define BROKER_LOCK_H

extern "C"
{
	void Broker_acquire_lock();
    void Broker_release_lock();
}

#endif
