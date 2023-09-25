cmake_minimum_required(VERSION 3.10)

project(Locking)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(locks)

add_subdirectory(leveldb)

# add_executable(smoke_test smoke.cpp)
# target_link_libraries(smoke_test PRIVATE locking PUBLIC OpenMP::OpenMP_CXX)
