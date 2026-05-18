add_executable(boost_tests
    main_test_boost.cpp
)

target_link_libraries(boost_tests PRIVATE src)
target_include_directories(boost_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_compile_options(boost_tests PRIVATE --coverage)

add_test(NAME BoostTests COMMAND boost_tests)