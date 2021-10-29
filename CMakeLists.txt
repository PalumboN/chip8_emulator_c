cmake_minimum_required (VERSION 3.9)

project(chip8)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)

add_library(Chip8Assembler src/assembler.c)
add_library(Chip8Lib src/chip8.c)

# Application, depending on SDL
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
add_executable(Chip8App src/main.c)
target_link_libraries(Chip8App ${SDL2_LIBRARIES})


add_executable(Chip8Bench src/mainBench.c)

target_link_libraries(Chip8App Chip8Lib)
target_link_libraries(Chip8Bench Chip8Lib)
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