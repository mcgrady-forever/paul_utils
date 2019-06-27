cmake_minimum_required(VERSION 2.8.8)
project(paul_utils)

add_subdirectory(${PROJECT_SOURCE_DIR}/deps/googletest/)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -Werror")

FILE(GLOB SRC "${PROJECT_SOURCE_DIR}/src/*.cc")
FILE(GLOB TESTS_SRC "${PROJECT_SOURCE_DIR}/tests/*.cc")

include_directories(
        ${PROJECT_SOURCE_DIR}/deps/googletest/googletest/include/
        ${PROJECT_SOURCE_DIR}/src/
)

foreach(_target
        thread_pool_unittest
        simple_thread_pool_unittest
        test
        )
    add_executable(${_target} "tests/${_target}.cc"
            )
    target_link_libraries(${_target}
            pthread
            curl
            gtest
            )
endforeach()