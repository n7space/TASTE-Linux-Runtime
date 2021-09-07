/**@file
 * This file is part of the TASTE Runtime Common.
 *
 * @copyright 2021 N7 Space Sp. z o.o.
 *
 * TASTE Runtime Common was developed under a programme of,
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

#include <chrono>
#include <thread>

namespace taste {
class Timer final {
public:
  Timer() = default;

  template <typename T>
  void run(std::chrono::milliseconds interval, T callback) {
    auto start = std::chrono::steady_clock::now();
    while (true) {
      using namespace std::chrono_literals;
      auto jitter = std::chrono::steady_clock::now() - start;
      auto diff = interval - jitter;
      if (diff > 0ms) {
        std::this_thread::sleep_for(diff);
      }
      callback();

      start = std::chrono::steady_clock::now();
    }
  }
};
} // namespace taste

#endif
