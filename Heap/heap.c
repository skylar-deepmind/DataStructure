//
// Created by Skylar X on 2025/9/18.
//
#include "heap.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static void swap(Item *a, Item *b) {
    Item temp = *a;
    *a = *b;
    *b = temp;
}

static void heap_up(Heap *h, size_t index) {
    if (index == 0) return;

    size_t parent_index = (index - 1) / 2;

    if (h->data[index] > h->data[parent_index]) {
        swap(&h->data[index], &h->data[parent_index]); //?????
        heap_up(h, parent_index);
    }
}

static void heap_down(Heap *h, size_t index) {
    size_t left_child_index = 2 * index + 1;
    size_t right_child_index = 2 * index + 2;
    size_t largest_index = index;

    if (left_child_index < h->size && h->data[left_child_index] > h->data[largest_index]) {
        largest_index = left_child_index;
    }

    if (right_child_index < h->size && h->data[right_child_index] > h->data[largest_index]) {
        largest_index = right_child_index;
    }

    if (largest_index != index) {
        swap(&h->data[index], &h->data[largest_index]);
        heap_down(h, largest_index);
    }
}

static int heap_resize(Heap *h) {
    size_t new_capacity = h->capacity * 2;
    Item *new_data = (Item *) realloc(h->data, new_capacity * sizeof(Item));
    if (!new_data) {
        return -1;
    }
    h->data = new_data;
    h->capacity = new_capacity;
    printf("[DEBUG] Heap resized to capacity %zu\n", new_capacity);

    return 0;
}

Heap *heap_create(size_t init_capacity) {
    if (init_capacity == 0) {
        init_capacity = 8;
    }

    Heap *h = (Heap *) malloc(sizeof(Heap));

    if (!h) {
        return NULL;
    }

    h->data = (Item *) malloc(init_capacity * sizeof(Item));

    if (!h->data) {
        free(h);
        return NULL;
    }

    h->size = 0;
    h->capacity = init_capacity;

    return h;
}

void heap_destroy(Heap **h) {
    if (h && *h) {
        free((*h)->data);
        (*h)->data = NULL;
        free(*h);
        *h = NULL;
    }
}

int heap_insert(Heap *h, Item value) {
    if (!h) return -1;

    if (h->size == h->capacity) {
        if (heap_resize(h) != 0) {
            return -1;
        }
    }

    h->data[h->size] = value;

    heap_up(h, h->size);

    h->size++;

    return 0;
}

int heap_extract_max(Heap *h, Item *max_value) {
    if (!h || is_heap_empty(h)) {
        return -1;
    }

    *max_value = h->data[0];

    h->data[0] = h->data[h->size - 1];
    h->size--;

    if (h->size > 0) {
        heap_down(h, 0);
    }

    return 0;
}

int heap_peek(const Heap *h, Item *peek_value) {
    if (!h || is_heap_empty(h)) {
        return -1;
    }

    *peek_value = h->data[0];

    return 0;
}

int is_heap_empty(const Heap *h) {
    if (h == NULL) return true;

    return h->size == 0;
}

size_t heap_size(const Heap *h) {
    if (!h) return 0;

    return h->size;
}

void heap_print_debug(const Heap *h) {
    if (!h) {

        printf("Heap is NULL.\n");

        return;

    }

    if (is_heap_empty(h)) {

        printf("Heap is empty.\n");

        return;

    }



    printf("Heap (size=%zu, capacity=%zu): [ ", h->size, h->capacity);

    for (size_t i = 0; i < h->size; ++i) {

        printf("%d ", h->data[i]);

    }

    printf("]\n");
}
