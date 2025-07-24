/**@file
 * This file is part of the TASTE Leon3 Runtime.
 *
 * @copyright 2025 N7 Space Sp. z o.o.
 *
 * Leon3 Runtime is free software: you can redistribute
 * it and/or modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the License,
 * or (at your option) any later version.
 *
 * You should have received a copy of the GNU General Public License
 * along with Leon3 Runtime. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Hal.h"

#include <chrono>
#include <thread>
#include <random>
#include <limits.h>

namespace taste {

bool
Hal::init()
{
    srand(time(0));
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
        return 0;
    }

    int32_t id = (rand() + 1) % INT_MAX;
    m_semaphores[m_created_semaphores_count++].m_id = id;

    return id;
}

bool
Hal::semaphoreObtain(int32_t id)
{
    uint32_t index;
    bool semapore_found = getSemaphoreIndex(id, index);

    if(!semapore_found) {
        return false;
    }

    m_semaphores[index].m_mutex.lock();

    return true;
}

bool
Hal::semaphoreRelease(int32_t id)
{
    uint32_t index;
    bool semapore_found = getSemaphoreIndex(id, index);

    if(!semapore_found) {
        return false;
    }

    m_semaphores[index].m_mutex.unlock();

    return true;
}

bool
Hal::getSemaphoreIndex(int32_t id, uint32_t& index)
{
    bool semapore_found = false;

    for(index = 0; index < m_created_semaphores_count; index++) {
        if(m_semaphores[index].m_id == id) {
            semapore_found = true;
            break;
        }
    }

    return semapore_found;
}

} // namespace taste