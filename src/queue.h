#ifndef TASTE_QUEUE_H
#define TASTE_QUEUE_H

#include <condition_variable>
#include <cstddef>
#include <mutex>
#include <queue>

#include "request.h"

namespace taste
{
	class Queue final
	{
	public:
		Queue(size_t max_elements);
		~Queue();

		Queue(const Queue&) = delete;
		Queue(Queue&&) = delete;

		Queue& operator=(const Queue&) = delete;
		Queue& operator=(Queue&&) = delete;

		void put(const Request& request);
		void get(Request& request);

	private:
		const size_t m_max_elements;
		mutable std::mutex m_mutex;
		mutable std::condition_variable m_cv;
		std::queue<Request> m_queue;

	};
}

#endif
