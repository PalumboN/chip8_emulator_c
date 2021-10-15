cmake_minimum_required (VERSION 3.9)

project(chip8)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

add_library(Chip8Assembler src/assembler.c)
add_library(Chip8Lib src/chip8.c)
add_executable(Chip8App src/main.c)

target_link_libraries(Chip8App Chip8Lib)
include_directories(include)

# Tests
enable_testing()

add_executable(Chip8Test 
	test/Chip8InterpreterTest.cpp
	test/Chip8AssemblerTest.cpp)
target_link_libraries(Chip8Test
  Chip8Lib
  Chip8Assembler
  gtest
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(Chip8Test)