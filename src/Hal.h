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

#ifndef HAL_H
#define HAL_H

/**
 * @file    Hal.h
 * @brief   Header for Hal
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

extern "C"
{
    /**
     * @brief               Initializes the Hal module.
     *
     * @return              Bool indicating whether the initialization was
     *                      successful
     */
    bool Hal_Init(void);

    /**
     * @brief               Returns time elapsed from the initialization of the
     *                      runtime
     *
     * @return              Time elapsed from the initialization of the runtime
     */
    uint64_t Hal_GetElapsedTimeInNs(void);

    /**
     * @brief               Suspends the current thread for the given amount of time
     *
     * @param[in] time_ns   time in nanoseconds
     *
     * @return              Bool indicating whether the sleep was successful
     */
    bool Hal_SleepNs(uint64_t time_ns);

    /**
     * @brief               Creates an RTOS backed semaphore. This function is not
     *                      thread safe, but it is assumed to be used only during
     *                      system initialization, from a single thread/Init task.
     *
     * @return              ID of the created semaphore
     */
    int32_t Hal_SemaphoreCreate(void);

    /**
     * @brief               Obtains the indicated semaphore, suspending the
     *                      execution of the current thread if necessary.
     *
     * @param[in] id        id of the semaphore
     *
     * @return              Bool indicating whether the obtain was successful
     */
    bool Hal_SemaphoreObtain(int32_t id);

    /**
     * @brief               Releases the indicated semaphore, potentially resuming
     *                      threads waiting on the semaphore
     *
     * @param[in] id        id of the semaphore
     *
     * @return              Bool indicating whether the release was successful
     */
    bool Hal_SemaphoreRelease(int32_t id);
}

#endif