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

#include "HalInternal.h"

#include <chrono>
#include <thread>
#include <limits.h>

namespace taste {

bool
Hal::init()
{
    m_init_time_stamp = std::chrono::steady_clock::now();
    m_created_semaphores_count = 0;

    return true;
}

uint64_t
Hal::getElapsedTimeInNs(void)
{
    std::chrono::steady_clock::time_point now_time_stamp = std::chrono::steady_clock::now();

    auto elapsed_time =
            std::chrono::duration_cast<std::chrono::nanoseconds>(now_time_stamp - m_init_time_stamp).count();

    if(elapsed_time > 0) {
        return (uint64_t)elapsed_time;
    } else {
        return 0;
    }
}

bool
Hal::sleepNs(uint64_t time_ns)
{
    std::this_thread::sleep_for(std::chrono::nanoseconds(time_ns));
    return true;
}

int32_t
Hal::semaphoreCreate(void)
{
    if(m_created_semaphores_count >= RT_MAX_HAL_SEMAPHORES) {
        return -1;
    }

    m_created_semaphores_count++;

    return (int32_t)m_created_semaphores_count;
}

bool
Hal::semaphoreObtain(int32_t id)
{
    m_semaphores[id].lock();

    return true;
}

bool
Hal::semaphoreRelease(int32_t id)
{
    m_semaphores[id].unlock();

    return true;
}

} // namespace taste