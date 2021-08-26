add_library(LinuxRuntime STATIC)
target_sources(LinuxRuntime
  PRIVATE      broker_lock.h
               lock.h
               queue.h
               request.h
               thread.h
               timer.h
  PUBLIC       lock.cpp
               thread.cpp
               broker_lock.cpp)

add_format_target(LinuxRuntime)
