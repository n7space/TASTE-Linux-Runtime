/**@file
 * This file is part of the TASTE Linux Runtime.
 *
 * @copyright 2021 N7 Space Sp. z o.o.
 *
 * TASTE Linux Runtime was developed under a programme of,
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

/**
 * @file    Queue.h
 * @brief   Message queue implementation for TASTE.
 */

#include <condition_variable>
#include <cstddef>
#include <iostream>
#include <mutex>
#include <queue>

#include <sched.h>

#include "Request.h"

namespace taste {
/**
 * @brief    Message queue implmentation.
 *
 * @tparam PARAMETER_SIZE The maximum size of single request in bytes.
 */
template<size_t PARAMETER_SIZE>
class Queue final
{
  public:
    /**
     * @brief Constructor
     *
     * @param max_elements    Maximum number of elements
     */
    Queue(const size_t max_elements);

    /// @brief deleted copy constructor
    Queue(const Queue&) = delete;

    /// @brief deleted move constructor
    Queue(Queue&&) = delete;

    /// @brief deleted copy assignment operator
    Queue& operator=(const Queue&) = delete;

    /// @brief deleted move assignment operator
    Queue& operator=(Queue&&) = delete;

    /**
     * @brief Put message into queue
     *
     * If queue is full the request will be dropped.
     * After successfull operation, the waiting thread will be notified.
     *
     * @param request  The request which will be inserted into queue
     */
    void put(const Request<PARAMETER_SIZE>& request);

    /**
     * @brief Put raw data into queue
     *
     * This function creates appropriate Request with given data before
     * putting it into queue.
     * If queue is full the request will be dropped.
     * If length is larger than PARAMETER_SIZE the request will be dropped.
     * After successfull operation, the waiting thread will be notified.
     *
     * @param data    The buffer with the request data
     * @param length  The length of the request
     */
    void put(const uint8_t* data, size_t length);

    /**
     * @brief Get request from queue.
     *
     * If queue is empty, the function waits for a request.
     *
     * @return The request reveived from queue.
     */
    void get(Request<PARAMETER_SIZE>& request);

    /**
     * @brief Checks if queue is empty.
     *
     * @return true is queue is empty, otherwise false
     */
    bool is_empty() const;

  private:
    const size_t m_max_elements;
    mutable std::mutex m_mutex;
    mutable std::condition_variable m_cv;
    std::queue<Request<PARAMETER_SIZE>> m_queue;
};

template<size_t PARAMETER_SIZE>
Queue<PARAMETER_SIZE>::Queue(const size_t max_elements)
    : m_max_elements(max_elements)
{
}

template<size_t PARAMETER_SIZE>
void
Queue<PARAMETER_SIZE>::put(const Request<PARAMETER_SIZE>& request)
{
    m_mutex.lock();
    if(m_queue.size() >= m_max_elements) {
        std::cerr << "Message loss - queue is full, " << m_max_elements << " allowed" << std::endl;
        m_mutex.unlock();
    } else {
        m_queue.push(request);
        m_mutex.unlock();
        m_cv.notify_one();
        sched_yield();
    }
}

template<size_t PARAMETER_SIZE>
void
Queue<PARAMETER_SIZE>::put(const uint8_t* data, size_t length)
{
    m_mutex.lock();
    static Request<PARAMETER_SIZE> request;

    if(length > PARAMETER_SIZE) {
        std::cerr << "Internal error - queue accepts messages with size " << PARAMETER_SIZE << std::endl;
        m_mutex.unlock();
    }

    memcpy(request.data(), data, length);
    request.set_length(length);

    if(m_queue.size() > m_max_elements) {
        std::cerr << "Message loss - queue is full, " << m_max_elements << " allowed" << std::endl;
        m_mutex.unlock();
    } else {
        m_queue.push(request);
        m_mutex.unlock();
        m_cv.notify_one();
        sched_yield();
    }
}

template<size_t PARAMETER_SIZE>
void
Queue<PARAMETER_SIZE>::get(Request<PARAMETER_SIZE>& request)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    while(true) {
        if(m_queue.empty()) {
            m_cv.wait(lock);
        } else {
            request = m_queue.front();
            m_queue.pop();
            lock.unlock();
            return;
        }
    }
}

template<size_t PARAMETER_SIZE>
bool
Queue<PARAMETER_SIZE>::is_empty() const
{
    std::unique_lock<std::mutex> lock(m_mutex);
    return m_queue.empty();
}
} // namespace taste

#endif
