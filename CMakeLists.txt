cmake_minimum_required(VERSION 3.6)
project(DBMS)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES dbms.cpp parser.h parser.cpp table.h table.cpp engine.cpp engine.h Utilities.h Utilities.cpp SelectQ.h SelectQ.cpp)
add_executable(DBMS ${SOURCE_FILES} dbms.cpp)
