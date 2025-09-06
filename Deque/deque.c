//
// Created by Skylar X on 2025/9/6.
//
#include "deque.h"
#include <stdlib.h>
#include <string.h>

struct Deque {
    void *data;
    size_t capacity;
    size_t element_size;
    size_t size;
    int front;
    int rear;
};

Deque *deque_create(size_t capacity, size_t element_size) {
    if (capacity == 0 || element_size ==0) {
        return NULL;
    }

    Deque* deque = (Deque*)malloc(sizeof(Deque));

    if (!deque) return NULL;

    deque->data = malloc(element_size * capacity);

    if (!deque->data) {
        free(deque);
        return NULL;
    }

    deque->capacity = capacity;

    deque->element_size = element_size;

    deque->size = 0;

    deque->front = 0;

    deque->rear = 0;

    return deque;
}

void deque_destroy(Deque **p_deque) {
    if (p_deque && *p_deque) {
        free((*p_deque)->data);
        free(*p_deque);
        *p_deque = NULL;
    }
}

bool deque_push_front(Deque *deque, const void *element_data) {
    if (!deque || !element_data || deque_is_full(deque)) {
        return false;
    }

    deque->front = (deque->front - 1 + deque->capacity) % deque->capacity;

    void* target_address = (char*)deque->data + deque->front * deque->element_size;

    memcpy(target_address, element_data, deque->element_size);

    deque->size++;

    return true;
}

bool deque_push_back(Deque *deque, const void *element_data) {
    if (!deque || !element_data || deque_is_full(deque)) {
        return false;
    }

    void* target_address = (char*)deque->data + deque->rear * deque->element_size;

    memcpy(target_address, element_data, deque->element_size);

    deque->rear = (deque->rear + 1) % deque->capacity;

    deque->size++;

    return true;
}

bool deque_pop_front(Deque *deque, void *output_buffer) {
    if (!deque || !output_buffer || deque_is_empty(deque)) {
        return false;
    }

    void* source_address = (char*)deque->data + deque->element_size * deque->front;

    memcpy(output_buffer,source_address,deque->element_size);

    deque->front = (deque->front + 1) % deque->capacity;

    deque->size--;

    return true;
}

bool deque_pop_back(Deque *deque, void *output_buffer) {
    if (!deque || !output_buffer || deque_is_empty(deque)) {
        return false;
    }

    deque->rear = (deque->rear - 1 + deque->capacity) % deque->capacity;

    void* source_address = (char*)deque->data + deque->element_size * deque->rear;

    memcpy(output_buffer,source_address,deque->element_size);

    deque->size--;

    return true;
}

bool deque_peek_front(const Deque *deque, void *output_buffer) {
    if (!deque || !output_buffer || deque_is_empty(deque)) return false;

    void* source_address = (char*) deque->data + deque->front * deque->element_size;

    memcpy(output_buffer,source_address,deque->element_size);

    return true;
}

bool deque_peek_back(const Deque *deque, void *output_buffer) {
    if (!deque || !output_buffer || deque_is_empty(deque)) return false;

    int last_index = (deque->rear - 1 + deque->capacity) % deque->capacity;

    void* source_address = (char*) deque->data + deque->element_size * last_index;

    memcpy(output_buffer,source_address,deque->element_size);

    return true;
}

bool deque_is_empty(const Deque *deque) {
    if (!deque) {
        return true;
    }

    return deque->size == 0;
}

bool deque_is_full(const Deque *deque) {
    if (!deque) {
        return true;
    }

    return deque->size == deque->capacity;
}

size_t get_deque_size(const Deque *deque) {
    if (!deque) {
        return 0;
    }

    return deque->size;
}
