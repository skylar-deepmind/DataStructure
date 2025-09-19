cmake_minimum_required(VERSION 3.31)
project(Heap C)

set(CMAKE_C_STANDARD 11)

add_executable(Heap main.c
        heap.c
        heap.h)
