add_library(LinuxRuntime STATIC)
target_sources(LinuxRuntime
  PRIVATE      lock.h
               queue.h
               request.h
               thread.h
               timer.h
  PUBLIC       lock.cpp
               thread.cpp)

add_format_target(LinuxRuntime)
