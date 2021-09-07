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

#ifndef TASTE_LOCK_H
#define TASTE_LOCK_H

/**
 * @file     Lock.h
 * @brief    Implemntation of lock required by TASTE function blocks.
 *
 */

#include <mutex>

namespace taste {
/**
 * @brief Concurrency Lock implementation
 */
class Lock final {
public:
  /**
   * @brief Default constructor.
   *
   * Constructed lock is in 'unlocked' state.
   */
  Lock();
  Lock(const Lock &) = delete;
  Lock(Lock &&) = delete;

  Lock &operator=(const Lock &) = delete;
  Lock &operator=(Lock &&) = delete;

  /// @brief acquire lock
  void lock();
  /// @release lock
  void unlock();

private:
  std::mutex m_mutex;
};
} // namespace taste

#endif