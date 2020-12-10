cmake_minimum_required(VERSION 3.14)
project(finale)

set(CMAKE_CXX_STANDARD 14)

add_executable(finale main.cpp Header/Tools.hpp Source/Tools.cpp Header/HuffmanTree.hpp Source/HuffmanTree.cpp Header/HuffmanTreeNode.hpp Source/HuffmanTreeNode.cpp Header/AllMyClass.hpp Header/Service.hpp)