cmake_minimum_required(VERSION 3.0)

project(QuickSort)
set(CMAKE_CXX_STANDARD 17)

add_executable(
    test_quicksort
    tests/test_main.cpp
    tests/test_quicksort.cpp
)

add_subdirectory("dependencies/rapidcheck")
target_link_libraries(test_quicksort rapidcheck)
