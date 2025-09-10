cmake_minimum_required(VERSION 3.31)
project(BST C)

set(CMAKE_C_STANDARD 11)

add_executable(BST main.c
        bst.h
        bst.c)
