cmake_minimum_required(VERSION 3.17)
project(bjarne_scripts)

# GoogleTest requires at least C++14!
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/f8d7d77c06936315286eb55f8de22cd23c188571.zip #release 1.14
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()

# Set the source directory
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# List all your source files individually
set(SRC_FILES
    ${SRC_DIR}/Chrono.hpp
    ${SRC_DIR}/Chrono.cpp
    # Add more source files as needed
)

# Create the library target
add_library(my_library ${SRC_FILES})

# Set the include directories for the library target
target_include_directories(my_library PUBLIC ${SRC_DIR})

# Set the test directory
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)

# List all your test source files individually
set(TEST_SOURCES
    ${TEST_DIR}/test_chrono.cpp
    # Add more test source files as needed
)

# Create the test executable and name it tests
add_executable(tests ${TEST_SOURCES})

# Set the include directories for the test target
target_include_directories(tests PRIVATE ${SRC_DIR})

# Link necessary libraries
target_link_libraries(tests PRIVATE my_library gtest GTest::gtest_main)

# Following needs to be built with clang using Msys2 FML -- toolchain must be installed and paths updated, etc
## Enable AddressSanitizer for the tests executable
#set_target_properties(tests PROPERTIES
#    COMPILE_FLAGS "-fsanitize=address -fno-omit-frame-pointer"
#    LINK_FLAGS "-fsanitize=address"
#)
#
## Add a custom target to run all tests with AddressSanitizer
#add_custom_target(run-tests-asan
#    COMMAND ASAN_OPTIONS=symbolize=1 ./tests
#    DEPENDS tests
#)
#

# Discover tests and add them to CTest
include(GoogleTest)
gtest_discover_tests(tests)
