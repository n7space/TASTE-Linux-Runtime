#include "request.h"

#include <cstring>

namespace taste
{
	Request::Request() :
		m_length(0)
	{
	}

	Request::Request(const Request& other) :
		m_length(other.m_length)
	{
		memcpy(m_data, other.m_data, GENERIC_LINUX_BUFFER_SIZE);
	}

	Request::Request(Request&& other) :
		m_length(other.m_length)
	{
		memcpy(m_data, other.m_data, GENERIC_LINUX_BUFFER_SIZE);
	}

	Request& Request::operator=(const Request& rhs)
	{
		m_length = rhs.m_length;
		memcpy(m_data, rhs.m_data, GENERIC_LINUX_BUFFER_SIZE);
		return *this;
	}

	Request& Request::operator=(Request&& rhs)
	{
		m_length = rhs.m_length;
		memcpy(m_data, rhs.m_data, GENERIC_LINUX_BUFFER_SIZE);
		return *this;
	}
}
