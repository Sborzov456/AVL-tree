cmake_minimum_required(VERSION 3.16)
project(AVL C)

set(CMAKE_C_STANDARD 17)

add_executable(AVL main.c SecondaryFunctions.h SecondaryFunctions.c Tree.h Tree.c)
