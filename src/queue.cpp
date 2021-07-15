#include "queue.h"

#include <iostream>

namespace taste
{
	Queue::Queue(size_t max_elements) :
		m_max_elements(max_elements)
	{
	}

	Queue::~Queue()
	{
	}

	void Queue::put(const Request& request)
	{
		m_mutex.lock();
		if(m_queue.size() >= m_max_elements)
		{
			std::cerr << "Message loss - queue is full, " << m_max_elements << " allowed" << std::endl;
			m_mutex.unlock();
		}
		else
		{
			m_queue.push(request);
			m_mutex.unlock();
			m_cv.notify_one();
		}
	}

	void Queue::get(Request& request)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		while(true)
		{
			if(m_queue.empty())
			{
				m_cv.wait(lock);
			}
			else
			{
				request = m_queue.front();
				m_queue.pop();
				lock.unlock();
				return;
			}
		}
	}
}
