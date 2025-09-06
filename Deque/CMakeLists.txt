cmake_minimum_required(VERSION 3.31)
project(Deque C)

set(CMAKE_C_STANDARD 11)

add_executable(Deque main.c
        deque.h
        deque.c
)
