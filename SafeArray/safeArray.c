//
// Created by Skylar X on 2025/9/9.
//
#include <stdio.h>
#include <stdlib.h>
#include "safeArray.h"

struct SafeArray {
    int *data;
    size_t capacity;
};

static void _set_val(SafeArray *sarray, size_t index, int val) {
    sarray->data[index] = val;
}

static int _get_val(SafeArray *sarray, size_t index) {
    return sarray->data[index];
}

SafeArray *sarray_create(size_t capacity) {
    if (capacity == 0) return NULL;

    SafeArray *sarray = (SafeArray *) malloc(sizeof(SafeArray));
    if (!sarray) return NULL;

    sarray->data = (int *) malloc(capacity * sizeof(int));

    if (!sarray->data) {
        free(sarray);
        return NULL;
    }

    sarray->capacity = capacity;

    return sarray;
}

void *sarray_destroy(SafeArray **p_sarray) {
    if (!p_sarray && !*p_sarray) {
        free((*p_sarray)->data);
        free(*p_sarray);
        *p_sarray = NULL;
    }
}

bool sarray_set(SafeArray *sarray, size_t index, int val) {
    if (!sarray || index >= sarray->capacity) {
        return false;
    }

    _set_val(sarray, index, val);

    return true;
}

bool sarray_get(const SafeArray *sarray, size_t index, int *out_val) {
    if (!sarray || !out_val || index >= sarray->capacity) {
        return false;
    }

    int val = _get_val(sarray,index);

    *out_val = val;

    return true;
}

size_t sarray_get_capacity(const SafeArray *sarray) {
    if (!sarray) return 0;

    return sarray->capacity;
}

void sarray_print(const SafeArray *sarray) {
    if (!sarray) {
        printf("SafeArray is NULL.\n");
        return;
    }
    printf("SafeArray (capacity: %zu) [ ", sarray->capacity);
    for (size_t i = 0; i < sarray->capacity; i++) {
        // 为了打印，我们在这里“作弊”直接访问了内部数据。
        // 在实际应用中，我们甚至可以不提供打印函数，以保证绝对的封装。
        printf("%d ", sarray->data[i]);
    }
    printf("]\n");
}
