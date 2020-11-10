cmake_minimum_required(VERSION 3.12)

project(iz_2)
find_package(Threads REQUIRED)

# Флаги пользователя
option(TESTS "" OFF)
option(ENABLE_COVERAGE "" OFF)
# ========================================

# Флаги компиляции и флаги покрытия, если необходимы
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wpedantic")
if(ENABLE_COVERAGE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")
    set(CMAKE_C_OUTPUT_EXTENSION_REPLACE 1)
    set(CMAKE_CXX_FLAGS "--coverage -fprofile-arcs -ftest-coverage")
    set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)
endif()
# ========================================

# Добавление многопоточной библиотеки и линковка потоков к этой библиотеке
add_library(COUNTING_NUMBERS_THREADS SHARED lib/counting-numbers_p/counting-numbers_p.c)
target_link_libraries(COUNTING_NUMBERS_THREADS Threads::Threads)
# ========================================

# Добавление статической библиотеки
add_library(COUNTING_NUMBERS STATIC lib/counting-numbers_c/counting-numbers_c.c)
# ========================================

if(TESTS)
    find_package(GTest REQUIRED)

    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED on)

    add_definitions(-DSOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}" -DNUMBER_NUMBERS=2000000)

    add_executable(mainTest tests/TestFuncs.cpp)

    # Линкуем обе реализации библиотеки для проведения тестов без dlopen
    include_directories(${GTEST_INCLUDE_DIRS})
    target_link_libraries(
        mainTest  
        ${GTEST_LIBRARIES} 
        Threads::Threads 
        ${CMAKE_DL_LIBS} 
        COUNTING_NUMBERS 
        COUNTING_NUMBERS_THREADS
    )
    # ========================================
else()
    set(CMAKE_C_STANDARD 11)
    set(CMAKE_C_STANDARD_REQUIRED on)

    add_executable(main main.c)

    # Линкуем одну реализацию библиотеки для проведения тестов с dlopen
    target_link_libraries(main ${CMAKE_DL_LIBS} COUNTING_NUMBERS)
endif()
