cmake_minimum_required(VERSION 3.31)
project(DynamicArray C)

set(CMAKE_C_STANDARD 11)

# 指定头文件路径
include_directories(${PROJECT_SOURCE_DIR}/include)

# 可执行文件，包含 main.c 和库的实现文件
add_executable(DynamicArray
        main.c
        src/DynamicArray.c
)
