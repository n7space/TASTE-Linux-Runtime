#ifndef TASTE_REQUEST_H
#define TASTE_REQUEST_H

#include <cstdint>
#include <cstring>

namespace taste {
template <size_t PARAMETER_SIZE> struct Request final {
  Request() : m_length(0) {}

  Request(const Request &other) : m_length(other.m_length) {
    memcpy(m_data, other.m_data, PARAMETER_SIZE);
  }

  Request(Request &&other) : m_length(other.m_length) {
    memcpy(m_data, other.m_data, PARAMETER_SIZE);
  }

  Request &operator=(const Request &rhs) {
    m_length = rhs.m_length;
    memcpy(m_data, rhs.m_data, PARAMETER_SIZE);
    return *this;
  }

  Request &operator=(Request &&rhs) {
    m_length = rhs.m_length;
    memcpy(m_data, rhs.m_data, PARAMETER_SIZE);
    return *this;
  }

  uint32_t m_length;
  uint8_t m_data[PARAMETER_SIZE];
};
} // namespace taste

#endif
