cmake_minimum_required(VERSION 3.12)

project(iz_1)

option(TESTS "" OFF)
option(ENABLE_COVERAGE "" OFF)

set(SOURCE_LIB lib/decimal-to-roman/decimal-to-roman.c)
add_library(D_T_R SHARED ${SOURCE_LIB})	

if(TESTS)
    find_package(GTest REQUIRED)
    find_package(Threads REQUIRED)

    # cpp for gtest
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED on)

    if(ENABLE_COVERAGE)
        set(CMAKE_CXX_FLAGS "--coverage -fprofile-arcs -ftest-coverage")
        set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)
        set(CMAKE_C_FLAGS "--coverage")
        set(CMAKE_C_OUTPUT_EXTENSION_REPLACE 1)
    endif()

    include_directories(${GTEST_INCLUDE_DIRS})
    add_executable(mainTest tests/TestFuncs.cpp)
    target_link_libraries(mainTest  ${GTEST_LIBRARIES} Threads::Threads D_T_R)
else()
    set(CMAKE_C_STANDARD 11)
    set(CMAKE_C_STANDARD_REQUIRED on)

    if(ENABLE_COVERAGE)
        set(CMAKE_C_FLAGS "--coverage")
        set(CMAKE_C_OUTPUT_EXTENSION_REPLACE 1)
    endif()

    add_executable(main main.c)
    target_link_libraries(main D_T_R)
endif()
