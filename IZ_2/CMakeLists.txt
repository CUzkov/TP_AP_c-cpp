cmake_minimum_required(VERSION 3.12)

project(iz_2)

option(TESTS "" OFF)
option(ENABLE_COVERAGE "" OFF)

find_package(Threads REQUIRED)

add_library(C_N_P MODULE lib/counting-numbers_p/counting-numbers_p.c)
target_link_libraries(C_N_P Threads::Threads)

add_library(C_N_C STATIC lib/counting-numbers_c/counting-numbers_c.c)

if(ENABLE_COVERAGE)
    set(CMAKE_C_FLAGS "--coverage")
    set(CMAKE_C_OUTPUT_EXTENSION_REPLACE 1)
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wpedantic")

if(TESTS)
    find_package(GTest REQUIRED)

    # cpp for gtest
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED on)

    if(ENABLE_COVERAGE)
        set(CMAKE_CXX_FLAGS "--coverage -fprofile-arcs -ftest-coverage")
        set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)
    endif()

    include_directories(${GTEST_INCLUDE_DIRS})
    add_executable(mainTest tests/TestFuncs.cpp)
    target_link_libraries(mainTest  ${GTEST_LIBRARIES} Threads::Threads ${CMAKE_DL_LIBS} C_N_C)
else()
    set(CMAKE_C_STANDARD 11)
    set(CMAKE_C_STANDARD_REQUIRED on)

    add_executable(main main.c)
    target_link_libraries(main ${CMAKE_DL_LIBS} C_N_C)
endif()
