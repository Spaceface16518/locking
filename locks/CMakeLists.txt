project(Locks)

add_library(wrap SHARED wrap.cpp interpose.h)
set_property(TARGET wrap PROPERTY POSITION_INDEPENDENT_CODE ON)

# add_library(locking SHARED spin_loop.h cache_pad.h clh.cpp clh.h mcs.h mcs.cpp)
