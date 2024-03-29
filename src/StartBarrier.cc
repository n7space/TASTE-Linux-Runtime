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

#include "StartBarrier.h"
#include <iostream>

namespace taste {
void
StartBarrier::initialize(size_t number, InitCallback init_callback)
{
    m_init_callback = init_callback;

    const int error_code = pthread_barrier_init(&m_init_barrier, nullptr, number);
    if(error_code != 0) {
        std::cerr << "Barrier has not been created properly. Error code : " << error_code << std::endl;
        exit(EXIT_FAILURE);
    }
}

void
StartBarrier::wait()
{
    const int error_code = pthread_barrier_wait(&m_init_barrier);
    if(error_code != PTHREAD_BARRIER_SERIAL_THREAD && error_code != 0) {
        std::cerr << "Barrier Wait has been failed. Error code : " << error_code << std::endl;
        exit(EXIT_FAILURE);
    }

    std::call_once(m_init_callback_flag, m_init_callback);
}

pthread_barrier_t StartBarrier::m_init_barrier;
StartBarrier::InitCallback StartBarrier::m_init_callback;
std::once_flag StartBarrier::m_init_callback_flag;
} // namespace taste
