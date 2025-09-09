cmake_minimum_required(VERSION 3.31)
project(SafeArray C)

set(CMAKE_C_STANDARD 11)

add_executable(SafeArray main.c
        safeArray.h
        safeArray.c)
