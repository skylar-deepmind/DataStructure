//
// Created by Skylar X on 2025/9/5.
//
#include <stdlib.h>
#include <string.h>
#include "circularQueue.h"

struct CircularQueue {
    void *data;
    size_t element_size;
    size_t capacity;
    size_t size;
    int front;
    int rear;
};

Queue *queue_create(size_t capacity, size_t element_size) {
    if (capacity == 0 || element_size == 0) {
        return NULL;
    }
    Queue *queue = (Queue *) malloc(sizeof(Queue));
    if (!queue) {
        return NULL;
    }
    queue->data = malloc(element_size * capacity);
    if (!queue->data) {
        free(queue);
        return NULL;
    }
    queue->capacity = capacity;
    queue->size = 0;
    queue->element_size = element_size;
    queue->front = 0;
    queue->rear = 0;

    return queue;
}

void queue_destroy(Queue **p_queue) {
    if (p_queue && *p_queue) {
        free((*p_queue)->data);
        free(*p_queue);
        *p_queue = NULL;
    }
}

bool queue_enqueue(Queue *queue, const void *element_data) {
    if (!queue || !element_data) {
        return false;
    }

    if (queue->size == queue->capacity) {
        return false;
    }

    void *target_address = (char *) queue->data + (queue->rear * queue->element_size);

    memcpy(target_address, element_data, queue->element_size);

    queue->rear = (queue->rear + 1) % queue->capacity;

    queue->size++;

    return true;
}

bool queue_dequeue(Queue *queue, void *output_buffer) {
    if (!queue || !output_buffer) {
        return false;
    }

    if (queue->size == 0) {
        return false;
    }

    void *source_address = (char *) queue->data + (queue->element_size * queue->front);

    memcpy(output_buffer, source_address, queue->element_size);

    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;

    return true;
}

bool queue_peek(const Queue *queue, void *output_buffer) {
    if (!queue || !output_buffer) {
        return false;
    }

    if (queue->size == 0) {
        return false;
    }

    void *source_address = (char *) queue->data + (queue->element_size * queue->front);

    memcpy(output_buffer, source_address, queue->element_size);

    return true;
}

bool queue_is_empty(const Queue *queue) {
    if (queue == NULL) {
        return true;
    }

    return queue->size == 0;
}

bool queue_is_full(const Queue *queue) {
    if (!queue) return true; // 不存在的队列视为满，以免误操作⚠️
    return queue->size == queue->capacity;
}

size_t get_queue_size(const Queue *queue) {
    if (!queue) return 0;
    return queue->size;
}

size_t get_queue_capacity(const Queue *queue) {
    if (!queue) return 0;
    return queue->capacity;
}
