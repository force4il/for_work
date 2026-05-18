cmake_minimum_required(VERSION 3.16)
project(Lab4Structures)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(--coverage)
add_link_options(--coverage)

add_library(src STATIC
    src/stack.cpp
    src/queue.cpp
    src/tree.cpp
)
target_include_directories(src PUBLIC src)

enable_testing()
add_subdirectory(tests)
add_subdirectory(boost_tests)