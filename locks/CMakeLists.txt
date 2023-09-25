project(Locks)

add_library(wraplock SHARED wrap_lock.cpp)
set_property(TARGET wraplock PROPERTY POSITION_INDEPENDENT_CODE ON)

add_executable(wraplock_test wrap_test.c)
target_link_libraries(wraplock_test wraplock)

# add_library(locking SHARED spin_loop.h cache_pad.h clh.cpp clh.h mcs.h mcs.cpp)
