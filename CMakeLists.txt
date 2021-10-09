cmake_minimum_required(VERSION 3.19)
project(SharedPtr)

set(CMAKE_CXX_STANDARD 17)

add_executable(SharedPtr main.cpp SharedPtr.cpp SharedPtr.h)