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

#include "thread.h"

#include <iostream>

namespace taste {
void Thread::start(void (*method)()) {
  m_method = nullptr;
  m_param = nullptr;
  create_thread(&Thread::method_wrapper, reinterpret_cast<void *>(method));
}

void Thread::start(void (*method)(void *), void *param) {
  m_method = method;
  m_param = param;
  create_thread(&Thread::method_wrapper_with_parameter,
                reinterpret_cast<void *>(this));
}

Thread::Thread(int priority, size_t stack_size)
    : m_priority(priority), m_stack_size(stack_size) {}

void Thread::create_thread(void *(*fn)(void *), void *param) {
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

  res = pthread_create(&m_thread_id, &thread_attributes, fn, param);
  if (res != 0) {
    std::cerr << "Unable to create thread" << std::endl;
  }

  pthread_attr_destroy(&thread_attributes);
}

void *Thread::method_wrapper(void *param) {
  void (*method)() = reinterpret_cast<void (*)()>(param);
  method();

  return nullptr;
}

void *Thread::method_wrapper_with_parameter(void *param) {
  Thread *self = reinterpret_cast<Thread *>(param);

  void (*method)(void *) = self->m_method;
  method(self->m_param);

  return nullptr;
}

} // namespace taste
