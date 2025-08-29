#pragma once
#include <stddef.h>

typedef int Data;

typedef struct {
    Data *data;
    size_t size;
    size_t capacity;
} DynamicArray;

//create
DynamicArray *create_array(size_t initial_capacity);

//read
Data *read_array(DynamicArray *arr, size_t index);

//update
int update_array(DynamicArray *arr, size_t index, Data value);

//delete
int delete_array(DynamicArray *arr, size_t index);

//insert
int insert_array(DynamicArray *arr, size_t index, Data value);

//append
void append_array(DynamicArray *arr, Data value);

//destroy
void destroy_array(DynamicArray *arr);

//print
void print_array(DynamicArray *arr);
