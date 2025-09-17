cmake_minimum_required(VERSION 3.31)
project(AVL C)

set(CMAKE_C_STANDARD 11)

add_executable(AVL main.c
        avl.h
        avl.c)
