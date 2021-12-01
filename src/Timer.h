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

#ifndef TASTE_TIMER_H
#define TASTE_TIMER_H

/**
 * @file    Timer.h
 * @brief   Timer for cyclic interfaces in TASTE
 */

#include <chrono>
#include <thread>

namespace taste {
/**
 * @brief Times is used to implement cyclic interfaces in TASTE
 */
class Timer final
{
  public:
    /**
     * @brief Execute given operation with given interval.
     *
     * @tparam T                callback type
     * @param dispatch_offset   dispatch offset value
     * @param interval          period value
     * @param callback          function like object to execute
     */
    template<typename T>
    static void run(const std::chrono::milliseconds dispatch_offset,
                    const std::chrono::milliseconds interval,
                    T callback);

    /**
     * @brief Initialize Timer
     *
     * This shall be used before starthing threads.
     * This method initializes start time, which is used by all cyclic interfaces
     * to schedule execution.
     */
    static void initialize();

  private:
    static std::chrono::steady_clock::time_point m_global_start_time;
};

template<typename T>
void
Timer::run(const std::chrono::milliseconds dispatch_offset, const std::chrono::milliseconds period, T callback)
{
    auto wakeup_time = m_global_start_time + dispatch_offset;
    while(true) {
        std::this_thread::sleep_until(wakeup_time);
        callback();
        wakeup_time = wakeup_time + period;
    }
}

} // namespace taste

#endif
