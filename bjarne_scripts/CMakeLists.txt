cmake_minimum_required(VERSION 3.17)
project(bjarne_scripts)

# GoogleTest requires at least C++14!
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG b796f7d44681514f58a683a3a71ff17c94edb0c1 # release-1.13, update often
  OVERRIDE_FIND_PACKAGE
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()

# Set the source directory
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# List all your source files individually
set(TEST_SOURCES
    ${SRC_DIR}/myVector.cpp
    ${SRC_DIR}/test_myVector.cpp
    # Add more source files as needed
)

# Create the test executable and name it tests
add_executable(tests ${TEST_SOURCES})

# Set the include directories for the tests target
target_include_directories(tests PRIVATE ${SRC_DIR})

# Link necessary libraries
target_link_libraries(tests PRIVATE gtest GTest::gtest_main)

# Add a custom target to run all tests
add_custom_target(run-tests COMMAND ${CMAKE_CTEST_COMMAND} --verbose --parallel
                  DEPENDS tests)

# Discover tests and add them to CTest
include(GoogleTest)
gtest_discover_tests(tests)

# Enable running specific tests with custom arguments
set(TEST_FILTER "" CACHE STRING "Filter for running specific tests")

# Add a custom target for running specific tests
add_custom_target(run-specific-tests
    COMMAND ${CMAKE_CTEST_COMMAND} --verbose --gtest_filter=${TEST_FILTER}
    DEPENDS tests
)

add_custom_target(run-bad-tests
    COMMAND ${CMAKE_CTEST_COMMAND} --rerun-failed --output-on-failure
    DEPENDS tests
)

# After compile to build, then can use "cmake --build build --target run-tests" to run all tests
# OR for specific tests, use 'cmake --build build --target run-specific-tests -- -DTEST_FILTER="XyzTest.NameOfTest" '
