include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE 
)
FetchContent_MakeAvailable(googletest)

add_executable(run_tests
    test_main.cpp
    test_stack.cpp
    test_queue.cpp
    test_tree.cpp
)

target_link_libraries(run_tests
    PRIVATE
    src
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(run_tests)