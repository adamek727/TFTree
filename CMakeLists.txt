cmake_minimum_required(VERSION 3.16)
project(TFTree)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(TFTree main.cpp include/TFTree/TFTree.h include/TFTree/TFNode.h include/TFTree/TF.h include/TFTree/TFChain.h)