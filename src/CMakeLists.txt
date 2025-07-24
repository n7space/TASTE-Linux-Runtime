add_library(LinuxRuntime STATIC)
target_sources(LinuxRuntime
  PRIVATE      BrokerLock.h
               Lock.h
               Queue.h
               Request.h
               Thread.h
               Timer.h
               StartBarrier.h
               Hal.h
  PUBLIC       Lock.cc
               Thread.cc
               BrokerLock.cc
               Timer.cc
               StartBarrier.cc
               Hal.cc)

add_format_target(LinuxRuntime)
