cmake_minimum_required(VERSION 3.21)
project(STL_Containers)

set(CMAKE_CXX_STANDARD 98)

add_executable(STL_Containers main.cpp Vector.hpp Iterator.hpp Utils.hpp)
