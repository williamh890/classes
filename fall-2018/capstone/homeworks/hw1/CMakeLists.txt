cmake_minimum_required(VERSION 3.9)

project(QuickSort)
set(CMAKE_CXX_STANDARD 14)

set(SRC_DIR, "src")
set(TEST_DIR, "tests")
include_directories(${SRC_DIR})
include_directories(${TEST_DIR})

add_executable(
    test_quicksort
    tests/test_main.cpp
    tests/test_quicksort.cpp
)

add_subdirectory("dependencies/rapidcheck")
target_link_libraries(test_quicksort rapidcheck)
