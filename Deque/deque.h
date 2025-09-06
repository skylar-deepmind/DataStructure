//
// Created by Skylar X on 2025/9/6.
//

#pragma once
#include <stdbool.h>
#include <stddef.h>

typedef struct Deque Deque;

Deque *deque_create(size_t capacity, size_t element_size);

void deque_destroy(Deque **p_deque);

bool deque_push_front(Deque *deque, const void *element_data);

bool deque_push_back(Deque *deque, const void *element_data);

bool deque_pop_front(Deque *deque, void *output_buffer);

bool deque_pop_back(Deque *deque, void *output_buffer);

bool deque_peek_front(const Deque *deque, void *output_buffer);

bool deque_peek_back(const Deque *deque, void *output_buffer);

bool deque_is_empty(const Deque *deque);

bool deque_is_full(const Deque *deque);

size_t get_deque_size(const Deque *deque);
