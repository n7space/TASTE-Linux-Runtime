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
#include <iostream>
#include <mutex>
#include <queue>

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
     * @param queue_name      Name of the queue used for error messages
     */
    Queue(const size_t max_elements, const char* queue_name);

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
     * @param sender_pid  The pid of the sender function
     * @param data        The buffer with the request data
     * @param length      The length of the request
     */
    void put(const asn1SccPID sender_pid, const uint8_t* data, size_t length);

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
    bool check_for_message_loss() const;

  private:
    const size_t m_max_elements;
    const char* m_queue_name;
    mutable std::mutex m_mutex;
    mutable std::condition_variable m_condition_variable;
    std::queue<Request<PARAMETER_SIZE>> m_queue;
};

template<size_t PARAMETER_SIZE>
Queue<PARAMETER_SIZE>::Queue(const size_t max_elements, const char* queue_name)
    : m_max_elements(max_elements)
    , m_queue_name(queue_name)
{
}

template<size_t PARAMETER_SIZE>
void
Queue<PARAMETER_SIZE>::put(const Request<PARAMETER_SIZE>& request)
{
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        if(check_for_message_loss()) {
            return;
        }

        m_queue.push(request);
    }

    m_condition_variable.notify_one();
}

template<size_t PARAMETER_SIZE>
void
Queue<PARAMETER_SIZE>::put(const asn1SccPID sender_pid, const uint8_t* data, size_t length)
{
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        if(check_for_message_loss()) {
            return;
        }

        m_queue.emplace(sender_pid, data, length);
    }

    m_condition_variable.notify_one();
}

template<size_t PARAMETER_SIZE>
void
Queue<PARAMETER_SIZE>::get(Request<PARAMETER_SIZE>& request)
{
    std::unique_lock<std::mutex> lock(m_mutex);

    while(true) {
        if(m_queue.empty()) {
            m_condition_variable.wait(lock);
        } else {
            request = m_queue.front();
            m_queue.pop();
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

template<size_t PARAMETER_SIZE>
bool
Queue<PARAMETER_SIZE>::check_for_message_loss() const
{
    if(m_queue.size() >= m_max_elements) {
        std::cerr << "Message loss in '" << m_queue_name << "' - queue is full, " << m_max_elements
                  << " elements are allowed" << std::endl;

        return true;
    }

    return false;
}

} // namespace taste

#endif
