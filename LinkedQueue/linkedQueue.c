//
// Created by Skylar X on 2025/9/5.
//
#include "linkedQueue.h"
#include <string.h>
#include <stdlib.h>

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

struct LinkedQueue {
    Node *front;
    Node *rear;
    size_t size;
    size_t element_size;
};

Queue *queue_create(size_t element_size) {
    if (element_size == 0) {
        return NULL;
    }
    Queue *queue = (Queue *) malloc(sizeof(Queue));
    if (queue == NULL) {
        return NULL;
    }
    queue->front = NULL;
    queue->rear = NULL;
    queue->element_size = element_size;
    queue->size = 0;

    return queue;
}

void queue_destroy(Queue **p_queue) {
    if (p_queue == NULL || *p_queue == NULL) return;

    Node *current = (*p_queue)->front;
    while (current != NULL) {
        Node *tmp = current;
        current = current->next;
        free(tmp->data);
        free(tmp);
    }
    free(*p_queue);
    *p_queue = NULL;
}

bool queue_enqueue(Queue *queue, const void *element_data) {
    if (!queue || !element_data) {
        return false;
    }

    Node *new_node = (Node *) malloc(sizeof(Node));
    if (!new_node) {
        free(new_node);
        return false;
    }

    new_node->data = malloc(queue->element_size);
    if (!new_node->data) {
        free(new_node->data);
        free(new_node);
        return false;
    }

    memcpy(new_node->data, element_data, queue->element_size);

    new_node->next = NULL;

    if (queue_is_empty(queue)) {
        queue->front = new_node;
        queue->rear = new_node;
    } else {
        queue->rear->next = new_node;
        queue->rear = new_node;
    }

    queue->size++;
    return true;
}

bool queue_dequeue(Queue *queue, void *output_buffer) {
    if (queue_is_empty(queue) || !output_buffer) {
        return false;
    }
    Node* tmp = queue->front;
    memcpy(output_buffer,tmp->data,queue->element_size);
    queue->front = tmp->next;

    if (queue->front == NULL) { // empty
        queue->rear = NULL;
    }

    free(tmp->data);
    free(tmp);

    queue->size--;
    return true;
}

bool queue_peek(const Queue *queue, void *output_buffer) {
    if (queue_is_empty(queue) || !output_buffer) {
        return false;
    }

    memcpy(output_buffer,queue->front->data,queue->element_size);

    return true;
}

bool queue_is_empty(const Queue *queue) {
    if (!queue) return true;

    return queue->size == 0;
}

size_t get_queue_size(const Queue *queue) {
    if (queue == NULL) {
        return 0;
    }

    return queue->size;
}
