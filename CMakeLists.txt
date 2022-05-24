cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

project(lab05)

option(BUILD_EXAMPLES "Build examples" OFF)
option(BUILD_TESTS "Build tests" ON)
option(BUILD_COVERAGE "Build coverage" OFF)

set(BUILD_TESTS ON)
set(BUILD_COVERAGE OFF)

include_directories(
        banking
)

add_subdirectory(banking)

if (BUILD_TESTS)
    include(FetchContent)
    FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
    )
    FetchContent_MakeAvailable(googletest)

    enable_testing()

    add_executable(
            banking_test
            tests/banking_test.cpp
    )
    target_link_libraries(
            banking_test
            banking
    )
    target_link_libraries(
            banking_test
            gtest_main
    )
    target_link_libraries(
            banking_test
            gmock
    )

    include(GoogleTest)
    gtest_discover_tests(banking_test)
endif ()
