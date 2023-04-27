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
#include <iostream>
#include "dataview-uniq.h"

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

    /**
     * @brief Constructor
     *
     * Constructs Request with provided arguments
     */
    Request(const asn1SccPID sender_pid, const uint8_t* const data, const size_t length);

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
    size_t length() const;

    /**
     * @brief set the request length
     *
     * The length shall be between 0 and PARAMETER_SIZE
     *
     * @param length   new length value
     */
    void set_length(size_t length);

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

    /**
     * @brief get the sender pid
     *
     * @return sender pid
     */
    asn1SccPID sender_pid() const;

    /**
     * @brief set the sender pid
     * 
     * @param sender_pid    sender pid
     */
    void set_sender_pid(asn1SccPID sender_pid);

  private:
    void check_length(size_t length) const;

  private:
    size_t m_length;
    asn1SccPID m_sender_pid;
    std::array<uint8_t, PARAMETER_SIZE> m_data;
};

template<size_t PARAMETER_SIZE>
Request<PARAMETER_SIZE>::Request()
    : m_length(0)
    , m_sender_pid(PID_env)
{
}

template<size_t PARAMETER_SIZE>
Request<PARAMETER_SIZE>::Request(const asn1SccPID sender_pid, const uint8_t* const data, const size_t length)
    : m_length(length)
    , m_sender_pid(sender_pid)
{
    check_length(length);

    memcpy(m_data.data(), data, length);
}

template<size_t PARAMETER_SIZE>
size_t
Request<PARAMETER_SIZE>::length() const
{
    return m_length;
}

template<size_t PARAMETER_SIZE>
void
Request<PARAMETER_SIZE>::set_length(size_t length)
{
    check_length(length);

    m_length = length;
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

template<size_t PARAMETER_SIZE>
asn1SccPID
Request<PARAMETER_SIZE>::sender_pid() const
{
    return m_sender_pid;
}

template<size_t PARAMETER_SIZE>
void
Request<PARAMETER_SIZE>::set_sender_pid(asn1SccPID sender_pid)
{
    m_sender_pid = sender_pid;
}

template<size_t PARAMETER_SIZE>
void
Request<PARAMETER_SIZE>::check_length(size_t length) const
{
    if(length > PARAMETER_SIZE) {
        std::cerr << "Request data size shall be <= " << PARAMETER_SIZE << " - new length value ("
                  << length << ") is greater than " << PARAMETER_SIZE << std::endl;

        exit(EXIT_FAILURE);
    }
}

} // namespace taste

#endif
