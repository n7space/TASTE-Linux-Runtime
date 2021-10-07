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

#ifndef START_BARRIER_H
#define START_BARRIER_H

/**
 * @file    StartBarrier.h
 * @brief   Implementation of thread barrier for synchronization of TASTE threads.
 */

#include <functional>
#include <mutex>

#include <pthread.h>

namespace taste {
/**
 * @brief StartBarrier used to synchronize threads in TASTE
 */
class StartBarrier
{
  public:
    /**
     * @brief Type definition of init callback function
     */
    using InitCallback = std::function<void()>;

    /**
     * @brief Deleted default constructor.
     */
    StartBarrier() = delete;

    /**
     * @brief Initialize StartBarrier.
     *
     * This function initializes StartBarrier to synchronize fixed amount of threads.
     * The initialization callback will be called only once,
     * before continuation of all threads
     *
     * @param number number of threads
     * @param init_callback callback which will be called once
     */
    static void initialize(size_t number, InitCallback init_callback);
    /**
     * @brief wait for all threads to reach this point and call init callback
     */
    static void wait();

  private:
    static pthread_barrier_t m_init_barrier;
    static InitCallback m_init_callback;
    static std::once_flag m_init_callback_flag;
};
} // namespace taste

#endif
