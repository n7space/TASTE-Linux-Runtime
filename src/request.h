#ifndef TASTE_REQUEST_H
#define TASTE_REQUEST_H

#include <cstddef>

#include <request_size.h>

namespace taste
{
	struct Request final
	{
		uint32_t m_length;
		uint8_t m_data[GENERIC_LINUX_BUFFER_SIZE];

		Request();

		Request(const Request& other);
		Request(Request&& other);

		Request& operator=(const Request& rhs);
		Request& operator=(Request&& rhs);
	};
}

#endif
