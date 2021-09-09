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

#ifndef TASTE_REQUEST_H
#define TASTE_REQUEST_H

/**
 * @file    Request.h
 * @brief   Request or message in TASTE system.
 */

#include <cstdint>
#include <cstring>
#include <array>

namespace taste {
/**
 * @brief Request or message used to implement sporadic interfaces in TASTE.
 *
 * @tparam PARAMETER_SIZE The maximum size of request in bytes.
 */
template<size_t PARAMETER_SIZE>
struct Request final
{
    /**
     * @brief Default constructor
     *
     * Constructs Request with length = 0
     */
    Request();

    /// @brief default copy constructor
    Request(const Request& other) = default;

    /// @brief default move constructor
    Request(Request&& other) = default;

    /// @brief default copy assignment operator
    Request& operator=(const Request& rhs) = default;

    /// @brief default move assignment operator
    Request& operator=(Request&& rhs) = default;

    /** @brief get length of the request in bytes
     *
     * @return the actual length of data
     */
    uint32_t length() const;

    /**
     * @brief set the request length
     *
     * The value shall be between 0 and PARAMETER_SIZE
     *
     * @param value    new length value
     */
    void set_length(uint32_t value);

    /**
     * @brief get the request data
     *
     * @return pointer to data
     */
    uint8_t* data();

    /**
     * @brief the buffer with the request data
     *
     * @return constant pointer to data
     */
    const uint8_t* data() const;

  private:
    uint32_t m_length;
    std::array<uint8_t, PARAMETER_SIZE> m_data;
};

template<size_t PARAMETER_SIZE>
Request<PARAMETER_SIZE>::Request()
    : m_length(0)
{
}

template<size_t PARAMETER_SIZE>
uint32_t
Request<PARAMETER_SIZE>::length() const
{
    return m_length;
}

template<size_t PARAMETER_SIZE>
void
Request<PARAMETER_SIZE>::set_length(uint32_t value)
{
    if(value <= PARAMETER_SIZE && value >= 0) {
        m_length = value;
    }
}

template<size_t PARAMETER_SIZE>
uint8_t*
Request<PARAMETER_SIZE>::data()
{
    return m_data.data();
}

template<size_t PARAMETER_SIZE>
const uint8_t*
Request<PARAMETER_SIZE>::data() const
{
    return m_data.data();
}
} // namespace taste

#endif
