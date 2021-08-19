#include "lock.h"

namespace taste {
Lock::Lock() {}

Lock::~Lock() {}

void Lock::lock() { m_mutex.lock(); }

void Lock::unlock() { m_mutex.unlock(); }
} // namespace taste
