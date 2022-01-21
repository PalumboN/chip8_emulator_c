cmake_minimum_required (VERSION 3.9)

project(chip8)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)

# Add here your targets, dependencies, include directories
add_library(Chip8Assembler src/assembler.c)
target_include_directories(Chip8Assembler PUBLIC include)

add_library(Chip8Lib src/chip8.c)
target_include_directories(Chip8Lib PUBLIC include)

add_executable(Chip8App src/main.c)
target_link_libraries(Chip8App Chip8Assembler Chip8Lib)


# Tests
enable_testing()

add_executable(Chip8Test 
    # Add here the files that make the test executable
    test/Chip8AssemblerTest.cpp
    test/Chip8InterpreterTest.cpp
)

target_link_libraries(Chip8Test
    # Add here the test dependencies
    Chip8Assembler
    Chip8Lib
    # Below, the google dependencies already included
    gtest
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(Chip8Test)