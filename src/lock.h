#ifndef TASTE_LOCK_H
#define TASTE_LOCK_H

#include <mutex>

namespace taste
{
	class Lock final
	{
	public:
		Lock();
		~Lock();
		Lock(const Lock&) = delete;
		Lock(Lock&&) = delete;

		Lock& operator=(const Lock&) = delete;
		Lock& operator=(Lock&&) = delete;

		void lock();
		void unlock();

	private:
		std::mutex m_mutex;

	};
}

#endif
