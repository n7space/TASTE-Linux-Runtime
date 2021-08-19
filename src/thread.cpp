#include "thread.h"

#include <iostream>

namespace taste {
void Thread::start(void (*method)()) {
  pthread_attr_t thread_attributes;

  int res = pthread_attr_init(&thread_attributes);
  if (res != 0) {
    std::cerr << "Unable to initialize thread attributes" << std::endl;
    return;
  }

  res = pthread_attr_setstacksize(&thread_attributes, m_stack_size);
  if (res != 0) {
    std::cerr << "Unable to set stack size in thread attributes" << std::endl;
    return;
  }

  int policy = SCHED_FIFO;
  res = pthread_attr_setschedpolicy(&thread_attributes, policy);
  if (res != 0) {
    std::cerr << "Unable to set sched policy in thread attributes" << std::endl;
    return;
  }

  int minimum_sched_priority = sched_get_priority_min(policy);
  int maximum_sched_priority = sched_get_priority_max(policy);

  if (m_priority < minimum_sched_priority ||
      m_priority > maximum_sched_priority) {
    std::cerr << "Invalid thread priority value." << std::endl;
    return;
  }

  sched_param sp;
  sp.sched_priority = m_priority;
  res = pthread_attr_setschedparam(&thread_attributes, &sp);
  if (res != 0) {
    std::cerr << "Unable to set priority in thread attributes" << std::endl;
    return;
  }

  res =
      pthread_create(&m_thread_id, &thread_attributes, &Thread::method_wrapper,
                     reinterpret_cast<void *>(method));
  if (res != 0) {
    std::cerr << "Unable to create thread" << std::endl;
  }

  pthread_attr_destroy(&thread_attributes);
}

Thread::Thread(int priority, size_t stack_size)
    : m_priority(priority), m_stack_size(stack_size) {}

void *Thread::method_wrapper(void *param) {
  void (*method)() = reinterpret_cast<void (*)()>(param);
  method();

  return nullptr;
}
} // namespace taste
