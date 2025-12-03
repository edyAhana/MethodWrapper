cmake_minimum_required(VERSION 3.10)
project(WrapperTest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB SRC_SOURCE src/*.cpp)

add_subdirectory(gtest)

file(GLOB TEST_SOURCE tests/*.cpp)

add_executable(run_test ${SRC_SOURCE} ${TEST_SOURCE})

target_link_libraries(run_test gtest gtest_main pthread)

add_test(NAME run_test COMMAND run_test)