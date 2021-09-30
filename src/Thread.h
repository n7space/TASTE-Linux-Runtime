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

#ifndef TASTE_THREAD_H
#define TASTE_THREAD_H

/**
 * @file    Thread.h
 * @brief   Thread implementation for TASTE
 */

#include <cstddef>
#include <pthread.h>

namespace taste {
/**
 * @brief Thread implementation for TASTE
 */
class Thread final
{
  public:
    /**
     * @brief Create a thread, without starting it
     *
     * @param priority     Priority of thread
     * @param stack_size   Stack size for new thread in bytes
     */
    Thread(const int priority, const size_t stack_size);

    /// @brief deleted copy constructor
    Thread(const Thread&) = delete;

    /// @brief deleted move constructor
    Thread(Thread&&) = delete;

    /// @brief deleted copy assignment operator
    Thread& operator=(const Thread&) = delete;

    /// @brief deleted move assignment operator
    Thread& operator=(Thread&&) = delete;

    /**
     * @brief Starts a thread
     *
     * @param method  A function which will be executed inside new thread.
     */
    void start(void (*method)());

    /**
     * @brief Starts a thread with parameter
     *
     * @param method  A function which will be executed inside new thread.
     * @param param   A parameter for function.
     */
    void start(void (*method)(void*), void* param);

    /// @brief Waits for the thread to finish
    void join();

  private:
    void create_thread(void* (*fn)(void*), void* param);
    static void* method_wrapper(void* param);
    static void* method_wrapper_with_parameter(void* param);

  private:
    int m_priority;
    int m_stack_size;
    pthread_t m_thread_id;

    void (*m_method)(void*);
    void* m_param;
};
} // namespace taste

#endif
