/**@file
 * This file is part of the TASTE Linux Runtime.
 *
 * @copyright 2025 N7 Space Sp. z o.o.
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

#ifndef TASTE_HAL_INTERNAL_H
#define TASTE_HAL_INTERNAL_H

/**
 * @file    Hal.h
 * @brief   Header for Hal
 */

#include <cstdbool>
#include <cstdint>
#include <cstdlib>
#include <mutex>

#ifndef RT_MAX_HAL_SEMAPHORES
#define RT_MAX_HAL_SEMAPHORES 8
#endif

namespace taste {

class Hal final
{
  public:
    Hal() = default;

    /**
     * @brief               Initializes the Hal module.
     *
     * @return              Bool indicating whether the initialization was
     *                      successful
     */
    static bool init();

    /**
     * @brief               Returns time elapsed from the initialization of the
     *                      runtime
     *
     * @return              Time elapsed from the initialization of the runtime
     */
    static uint64_t getElapsedTimeInNs();

    /**
     * @brief               Suspends the current thread for the given amount of time
     *
     * @param[in] time_ns   time in nanoseconds
     *
     * @return              Bool indicating whether the sleep was successful
     */
    static bool sleepNs(uint64_t time_ns);

    /**
     * @brief               Creates an RTOS backed semaphore. This function is not
     *                      thread safe, but it is assumed to be used only during
     *                      system initialization, from a single thread/Init task.
     *
     * @return              ID of the created semaphore
     */
    static int32_t semaphoreCreate(void);

    /**
     * @brief               Obtains the indicated semaphore, suspending the
     *                      execution of the current thread if necessary.
     *
     * @param[in] id        id of the semaphore
     *
     * @return              Bool indicating whether the obtain was successful
     */
    static bool semaphoreObtain(int32_t id);

    /**
     * @brief               Releases the indicated semaphore, potentially resuming
     *                      threads waiting on the semaphore
     *
     * @param[in] id        id of the semaphore
     *
     * @return              Bool indicating whether the release was successful
     */
    static bool semaphoreRelease(int32_t id);

  private:
    static std::chrono::steady_clock::time_point m_init_time_stamp;

    static uint32_t m_created_semaphores_count;
    static std::mutex m_semaphores[RT_MAX_HAL_SEMAPHORES];
};
} // namespace taste

#endif