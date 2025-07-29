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

#include "Hal.h"
#include "HalInternal.h"

extern "C"
{
    bool Hal_Init(void) { return taste::Hal::init(); }

    uint64_t Hal_GetElapsedTimeInNs(void) { return taste::Hal::getElapsedTimeInNs(); }

    bool Hal_SleepNs(uint64_t time_ns) { return taste::Hal::sleepNs(time_ns); }

    int32_t Hal_SemaphoreCreate(void) { return taste::Hal::semaphoreCreate(); }

    bool Hal_SemaphoreObtain(int32_t id) { return taste::Hal::semaphoreObtain(id); }

    bool Hal_SemaphoreRelease(int32_t id) { return taste::Hal::semaphoreRelease(id); }
}