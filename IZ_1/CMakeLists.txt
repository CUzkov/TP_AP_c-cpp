cmake_minimum_required(VERSION 3.12)

project(dz_1)

option(TESTS "" OFF)
option(ENABLE_COVERAGE "" OFF)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(SOURCE_LIB lib/decimal-to-roman/decimal-to-roman.cpp)

add_library(D_T_R STATIC ${SOURCE_LIB})	

if(ENABLE_COVERAGE)
    set(CMAKE_CXX_FLAGS "--coverage")
    set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)
endif()

if(TESTS)
    include_directories(${GTEST_INCLUDE_DIRS})
    add_executable(mainTest tests/TestFuncs.cpp)
    target_link_libraries(mainTest  ${GTEST_LIBRARIES} Threads::Threads D_T_R)
else()
    add_executable(main main.cpp)
    target_link_libraries(main D_T_R)
endif()
