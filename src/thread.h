#ifndef TASTE_THREAD_H
#define TASTE_THREAD_H

#include <cstddef>
#include <pthread.h>

namespace taste {
class Thread final {
public:
  Thread(int priority, size_t stack_size);
  Thread(const Thread &) = delete;
  Thread(Thread &&) = delete;
  Thread &operator=(const Thread &) = delete;
  Thread &operator=(Thread &&) = delete;

  void start(void (*method)());

private:
  static void *method_wrapper(void *param);

private:
  int m_priority;
  int m_stack_size;
  pthread_t m_thread_id;
};
} // namespace taste

#endif
