cmake_minimum_required(VERSION 3.21)
project(Isp)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")


set(SANITIZERS " -fsanitize=address -fsanitize=alignment -fsanitize=bool -fsanitize=bounds -fsanitize=enum -fsanitize=float-cast-overflow -fsanitize=float-divide-by-zero -fsanitize=integer-divide-by-zero -fsanitize=leak -fsanitize=nonnull-attribute -fsanitize=null -fsanitize=object-size -fsanitize=return -fsanitize=returns-nonnull-attribute -fsanitize=shift -fsanitize=signed-integer-overflow -fsanitize=undefined -fsanitize=unreachable -fsanitize=vla-bound -fsanitize=vptr")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SANITIZERS}")

add_executable(Sanitizers_tests src/pool.cpp src/pool.hpp src/tests.cpp)
add_executable(Valgrind_tests src/pool.cpp src/pool.hpp src/tests.cpp)

target_link_libraries(Sanitizers_tests gtest)
target_link_libraries(Valgrind_tests gtest)



add_executable(Sanitizers_performance src/pool.cpp src/pool.hpp src/performance.cpp)
add_executable(Valgrind_performance src/pool.cpp src/pool.hpp src/performance.cpp)




add_executable(Sanitizers_tests_2 src/pool_v2.cpp src/pool_v2.hpp src/tests.cpp)
add_executable(Valgrind_tests_2 src/pool_v2.cpp src/pool_v2.hpp src/tests.cpp)

target_link_libraries(Sanitizers_tests_2 gtest)
target_link_libraries(Valgrind_tests_2 gtest)

add_executable(Sanitizers_performance_2 src/pool_v2.cpp src/pool_v2.hpp src/performance.cpp)



add_executable(Sanitizers_tests_3 src/pool_v3.cpp src/pool_v3.hpp src/tests.cpp)
add_executable(Valgrind_tests_3 src/pool_v3.cpp src/pool_v3.hpp src/tests.cpp)

target_link_libraries(Sanitizers_tests_3 gtest)
target_link_libraries(Valgrind_tests_3 gtest)

add_executable(Sanitizers_performance_3 src/pool_v3.cpp src/pool_v3.hpp src/performance.cpp)

