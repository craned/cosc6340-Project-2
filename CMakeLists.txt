cmake_minimum_required(VERSION 3.6)
project(DBMS)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES dbms.cpp commandLine.cpp parser.h parser.cpp)
add_executable(DBMS ${SOURCE_FILES})