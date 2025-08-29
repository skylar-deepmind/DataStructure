#include <stdio.h>
#include <stdlib.h>
#include "DynamicArray.h"
#define INITIAL_CAPACITY 10

//辅助函数--》扩容/缩容
static int resize_array(DynamicArray *arr, size_t new_capacity) {
    //learing realloc
    Data *new_data = realloc(arr->data, sizeof(Data) * new_capacity);

    if (!new_data) {
        return -1;
    }

    arr->data = new_data;
    arr->capacity = new_capacity;

    return 0;
}

DynamicArray *create_array(size_t initial_capacity) {
    if (initial_capacity <= 0) {
        initial_capacity = INITIAL_CAPACITY;
    }

    DynamicArray *arr = (DynamicArray *) malloc(sizeof(DynamicArray));

    if (!arr) {
        return NULL;
    }

    arr->data = (Data *) malloc(sizeof(Data)*initial_capacity);

    if (!arr->data) {
        free(arr);
        return NULL;
    }

    arr->size = 0;
    arr->capacity = initial_capacity;

    return arr;
}

Data *read_array(DynamicArray *arr, size_t index) {
    if (index >= arr->size) {
        return NULL;
    }
    return &(arr->data[index]); //注意别写错了，函数要返回指针，要加&
}

int update_array(DynamicArray *arr, size_t index, Data value) {
    if (index >= arr->size) {
        return -1;
    }
    arr->data[index] = value;
    return 0;
}

int delete_array(DynamicArray *arr, size_t index) {
    if (index >= arr->size) {
        return -1;
    }
    for (size_t i = index; i < arr->size - 1; ++i) {
        arr->data[i] = arr->data[i + 1];
    }
    arr->size--;

    //当size降至capacity的1/4的时候，触发缩容
    if (arr->size > 0 && arr->size <= arr->capacity / 4 && arr->capacity > INITIAL_CAPACITY) {
        size_t new_capacity = arr->capacity / 2;

        if (new_capacity < arr->size) {
            new_capacity = arr->size;
        }
        if (new_capacity < INITIAL_CAPACITY) {
            new_capacity = INITIAL_CAPACITY;
        } //这两个卫语句真的会被触发吗？？？？？

        printf("\n---> [缩容警告!] Size (%zu) <= Capacity/4 (%zu). 准备缩容至 %zu. \n",

               arr->size, arr->capacity / 4, new_capacity);

        resize_array(arr, new_capacity);
    }
    return 0;
}

int insert_array(DynamicArray *arr, size_t index, Data value) {
    if (index > arr->size) {
        return -1;
    }

    if (arr->size >= arr->capacity) {
        if (resize_array(arr, arr->capacity * 2) != 0) {
            return -1;
        }
    } //理解这么写的原理，什么时候这么写

    for (size_t i = arr->size; i > index; --i) {
        arr->data[i] = arr->data[i - 1];
    }

    arr->data[index] = value;
    arr->size++;

    return 0;
}

//和上面那种，为什么扩容的写法不能一致呢？
void append_array(DynamicArray *arr, Data value) {
    if (arr->size >= arr->capacity) {
        resize_array(arr, arr->capacity * 2);
    }

    arr->data[arr->size] = value;
    arr->size++;
}

void destroy_array(DynamicArray *arr) {
    if (arr) {
        free(arr->data);
        free(arr);
    }
}

void print_array(DynamicArray *arr) {
    printf("\narr -> size : %zu,arr -> capacity : %zu\n",arr->size,arr->capacity);
    printf("[ ");
    for (size_t i = 0; i < arr->size; ++i) {
        printf("%d ",arr->data[i]);
    }
    printf("]");
}
