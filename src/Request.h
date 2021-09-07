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

#ifndef TASTE_REQUEST_H
#define TASTE_REQUEST_H

/**
 * @file    Request.h
 * @brief   Request or message in TASTE system.
 */

#include <cstdint>
#include <cstring>

namespace taste {
/**
 * @brief Request or message used to implement sporadic interfaces in TASTE.
 *
 * @tparam PARAMETER_SIZE The maximum size of request in bytes.
 */
template<size_t PARAMETER_SIZE>
struct Request final {
    /**
     * @brief Default constructor
     *
     * Constructs Request with length = 0
     */
    Request();

    /// @brief copy constructor
    Request(const Request& other);

    /// @brief move constructor
    Request(Request&& other);

    /// @brief copy assignment operator
    Request& operator=(const Request& rhs);

    /// @brief move assignment operator
    Request& operator=(Request&& rhs);

    /// @brief the length of the request in bytes
    uint32_t m_length;

    /// @brief the buffer with the request data
    uint8_t m_data[PARAMETER_SIZE];
};

template<size_t PARAMETER_SIZE>
Request<PARAMETER_SIZE>::Request()
    : m_length(0)
{
}

template<size_t PARAMETER_SIZE>
Request<PARAMETER_SIZE>::Request(const Request& other)
    : m_length(other.m_length)
{
    memcpy(m_data, other.m_data, PARAMETER_SIZE);
}

template<size_t PARAMETER_SIZE>
Request<PARAMETER_SIZE>::Request(Request&& other)
    : m_length(other.m_length)
{
    memcpy(m_data, other.m_data, PARAMETER_SIZE);
}

template<size_t PARAMETER_SIZE>
Request<PARAMETER_SIZE>&
Request<PARAMETER_SIZE>::operator=(const Request& rhs)
{
    m_length = rhs.m_length;
    memcpy(m_data, rhs.m_data, PARAMETER_SIZE);
    return *this;
}

template<size_t PARAMETER_SIZE>
Request<PARAMETER_SIZE>&
Request<PARAMETER_SIZE>::operator=(Request&& rhs)
{
    m_length = rhs.m_length;
    memcpy(m_data, rhs.m_data, PARAMETER_SIZE);
    return *this;
}

} // namespace taste

#endif
