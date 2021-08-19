#ifndef TASTE_QUEUE_H
#define TASTE_QUEUE_H

#include <condition_variable>
#include <cstddef>
#include <iostream>
#include <mutex>
#include <queue>

#include <sched.h>

#include "request.h"

namespace taste {
template <size_t PARAMETER_SIZE> class Queue final {
public:
  Queue(size_t max_elements) : m_max_elements(max_elements) {}

  ~Queue() {}

  Queue(const Queue &) = delete;
  Queue(Queue &&) = delete;

  Queue &operator=(const Queue &) = delete;
  Queue &operator=(Queue &&) = delete;

  void put(const Request<PARAMETER_SIZE> &request) {
    m_mutex.lock();
    if (m_queue.size() >= m_max_elements) {
      std::cerr << "Message loss - queue is full, " << m_max_elements
                << " allowed" << std::endl;
      m_mutex.unlock();
    } else {
      m_queue.push(request);
      m_mutex.unlock();
      m_cv.notify_one();
      sched_yield();
    }
  }

  void get(Request<PARAMETER_SIZE> &request) {
    std::unique_lock<std::mutex> lock(m_mutex);
    while (true) {
      if (m_queue.empty()) {
        m_cv.wait(lock);
      } else {
        request = m_queue.front();
        m_queue.pop();
        lock.unlock();
        return;
      }
    }
  }

  bool empty() const {
    std::unique_lock<std::mutex> lock(m_mutex);
    return m_queue.empty();
  }

private:
  const size_t m_max_elements;
  mutable std::mutex m_mutex;
  mutable std::condition_variable m_cv;
  std::queue<Request<PARAMETER_SIZE>> m_queue;
};
} // namespace taste

#endif
