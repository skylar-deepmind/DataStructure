//
// Created by Skylar X on 2025/9/5.
//
#pragma once
#include <stddef.h>
#include <stdbool.h>

typedef struct LinkedQueue Queue;

Queue *queue_create(size_t element_size);

void queue_destroy(Queue **p_queue);

bool queue_enqueue(Queue *queue, const void *element_data);

bool queue_dequeue(Queue *queue, void *output_buffer);

bool queue_peek(const Queue *queue, void *output_buffer);

bool queue_is_empty(const Queue *queue);

size_t get_queue_size(const Queue *queue);
