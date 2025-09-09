//
// Created by Skylar X on 2025/9/9.
//
#pragma once
#include <stddef.h>
#include <stdbool.h>

typedef struct SafeArray SafeArray;

SafeArray *sarray_create(size_t capacity);

void *sarray_destroy(SafeArray **p_sarray);

bool sarray_set(SafeArray *sarray, size_t index, int val);

bool sarray_get(const SafeArray *sarray, size_t index, int *out_val);

size_t sarray_get_capacity(const SafeArray *sarray);

void sarray_print(const SafeArray *sarray);
