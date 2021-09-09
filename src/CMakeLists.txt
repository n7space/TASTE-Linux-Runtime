add_library(LinuxRuntime STATIC)
target_sources(LinuxRuntime
  PRIVATE      BrokerLock.h
               Lock.h
               Queue.h
               Request.h
               Thread.h
               Timer.h
  PUBLIC       Lock.cpp
               Thread.cpp
               BrokerLock.cpp)

add_format_target(LinuxRuntime)
