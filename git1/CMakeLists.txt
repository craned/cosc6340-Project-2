cmake_minimum_required(VERSION 3.6)
project(git2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp parser.h parser.cpp table.h table.cpp)
add_executable(git2 ${SOURCE_FILES})