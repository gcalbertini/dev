cmake_minimum_required(VERSION 3.14)
project(bjarne_scripts)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing() # enables the use of the add_test() command and other testing-related functionality provided by CMake

include_directories(
    src
    # Add more include directories as needed
)
set(TEST_HEADERS
    src/utils.hpp
    src/Chrono.hpp
    # Add more header files as needed
)

set(TEST_SOURCES
    src/Chrono.cpp
    src/test_chrono.cpp
    # Add more source files as needed
)

# Create the test executable
add_executable(tests ${TEST_HEADERS} ${TEST_SOURCES})


# Link necessary libraries
target_link_libraries(tests gtest GTest::gtest_main)

# Discover tests and add them to CTest
include(GoogleTest)
gtest_discover_tests(tests)