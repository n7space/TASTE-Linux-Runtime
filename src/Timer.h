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
     * @tparam T         callback type
     * @param interval   interval value
     * @param callback   function like object to execute.
     */
    template<typename T>
    void run(const std::chrono::milliseconds interval, T callback);
};

template<typename T>
void
Timer::run(const std::chrono::milliseconds interval, T callback)
{
    auto wakeupTime = std::chrono::steady_clock::now();
    while(true) {
        wakeupTime = wakeupTime + interval;
        std::this_thread::sleep_until(wakeupTime);
        callback();
    }
}

} // namespace taste

#endif
