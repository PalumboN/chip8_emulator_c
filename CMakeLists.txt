cmake_minimum_required (VERSION 3.9)

project(chip8)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)

# Add here your targets, dependencies, include directories

# Tests
enable_testing()

add_executable(Chip8Test 
    # Add here the files that make the test executable
)
target_link_libraries(Chip8Test
    # Add here the test dependencies
    # Below, the google dependencies already included
    gtest
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(Chip8Test)