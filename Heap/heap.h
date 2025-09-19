//
// Created by Skylar X on 2025/9/18.
//

#pragma once
#include <stdlib.h>

typedef int Item;

typedef struct {
    Item *data;
    size_t size;
    size_t capacity;
} Heap;

Heap *heap_create(size_t init_capacity);

void heap_destroy(Heap **h);

int heap_insert(Heap *h, Item value);

int heap_extract_max(Heap *h, Item *max_value);

int heap_peek(const Heap *h, Item *peek_value);

int is_heap_empty(const Heap *h);

size_t heap_size(const Heap *h);

void heap_print_debug(const Heap *h);
