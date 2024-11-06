if (BUILD_TESTING)
    add_executable(tests general_test.cpp)
    target_link_libraries(prefixes PRIVATE GTest::gtest_main cxx_setup main)

    include(GoogleTest)
    gtest_discover_tests(prefixes)
endif()
