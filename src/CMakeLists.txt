add_library(LinuxRuntime STATIC)
target_sources(LinuxRuntime
  PRIVATE      BrokerLock.h
               Lock.h
               Queue.h
               Request.h
               Thread.h
               Timer.h
			   StartBarrier.h
  PUBLIC       Lock.cpp
               Thread.cpp
               BrokerLock.cpp
               Timer.cpp
			   StartBarrier.cpp)

add_format_target(LinuxRuntime)
