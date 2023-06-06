cmake_minimum_required(VERSION 3.14)
project(bjarne_scripts)

# GoogleTest requires at least C++14
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

enable_testing() # enables the use of Ctest

include_directories(
    src
    # Add more include directories as needed
)
set(TEST_HEADERS
    src/utils.hpp
    src/naiveLList.hpp
    #src/Chrono.hpp
    # Add more header files as needed
)

set(TEST_SOURCES
    #src/Chrono.cpp
    #src/test_chrono.cpp
    src/test_naiveLList.cpp
    src/naiveLList.cpp
    # Add more source files as needed
)

# Create the test executable and name it tests
add_executable(tests ${TEST_HEADERS} ${TEST_SOURCES})

# Set the TEST_EXECUTABLE variable
set(TEST_EXECUTABLE "tests")

# Link necessary libraries
target_link_libraries(${TEST_EXECUTABLE} gtest GTest::gtest_main)

# Add a custom test target
add_custom_target(run-tests COMMAND ${TEST_EXECUTABLE} DEPENDS ${TEST_EXECUTABLE})

# Enable running specific tests with custom arguments
add_test(NAME MyTests COMMAND ${TEST_EXECUTABLE})

# Define a CMake variable for specifying the test filter
set(TEST_FILTER "" CACHE STRING "Filter for running specific tests")

# Add a custom target for running specific tests
add_custom_target(run-specific-tests
    COMMAND ${CMAKE_CTEST_COMMAND} --verbose --gtest_filter=${TEST_FILTER}
    DEPENDS ${TEST_EXECUTABLE}
   # WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Discover tests and add them to CTest
include(GoogleTest)
gtest_discover_tests(tests)

# After compile to build, then can "cmake --build . --target run-tests" after this for all tests 
# OR for specifc tests,            'cmake --build . --target run-specific-tests -- -DTEST_FILTER="XyzTest.NameOfTest" '
