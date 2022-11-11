cmake_minimum_required(VERSION 3.21)
project(STL_Containers)

set(CMAKE_CXX_STANDARD 98)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")

add_executable(STL_Containers main.cpp Vector.hpp Iterator.hpp Utils.hpp)
