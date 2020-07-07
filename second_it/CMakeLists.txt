cmake_minimum_required(VERSION 3.16)
project(second_it)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(second_it main.cpp include/TFTree.h)