/**@file
 * This file is part of the TASTE Runtime Common.
 *
 * @copyright 2021 N7 Space Sp. z o.o.
 *
 * TASTE Runtime Common was developed under a programme of,
 * and funded by, the European Space Agency (the "ESA").
 *
 * Licensed under the ESA Public License (ESA-PL) Permissive,
 * Version 2.3 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://essr.esa.int/license/list
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef TASTE_QUEUE_H
#define TASTE_QUEUE_H

#include <condition_variable>
#include <cstddef>
#include <iostream>
#include <mutex>
#include <queue>

#include <sched.h>

#include "Request.h"

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

  void put(const uint8_t *data, size_t length) {
    m_mutex.lock();
    static Request<PARAMETER_SIZE> request;
    memcpy(request.m_data, data, length);
    request.m_length = length;

    if (m_queue.size() > m_max_elements) {
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

  bool is_empty() const {
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
