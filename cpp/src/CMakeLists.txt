add_library(src STATIC
    stack.cpp
    queue.cpp
    tree.cpp
)

target_include_directories(src PUBLIC .)