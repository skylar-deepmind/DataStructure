#include <stdlib.h>
#include <string.h>
#include "linkedStack.h"

#include <stdio.h>
#include <time.h>

typedef struct Node {
    void* data;
    struct Node* next;
}Node;

struct LinkedStack {
    Node* top;
    size_t element_size;
    size_t size;
};

Stack* stack_create(size_t element_size) {
    if (element_size == 0) {
        printf("Invalid parameters!!!");
        return NULL;
    }
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL) {
        printf("Failed to allocate memory for the new stack!!!");
        return NULL;
    }

    stack->top = NULL;
    stack->element_size = element_size;
    stack->size = 0;

    return stack;
}

void stack_destroy(Stack** p_stack) {
    if (p_stack == NULL || *p_stack == NULL) {
        return ;
    }

    Stack *curStack = *p_stack;//理解这种写法？？？？？还是感觉没理解到位
    Node* current = curStack->top;

    while (current != NULL) {
        Node* tmp = current;
        current = current->next;
        free(tmp->data);
        free(tmp);
    }
    free(curStack);
    *p_stack = NULL;
}

bool stack_push(Stack* stack,const void* element_data) {
    if (stack == NULL || element_data == NULL) {
        printf("Invalid parameters!!!");
        return false;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Failed to allocate memory for the new Node!!!");
        return false;
    }

    newNode->data = malloc(stack->element_size);
    if (newNode->data == NULL) {
        printf("Failed to allocate memory for the new data!!!");
        return false;
    }

    memcpy(newNode->data,element_data,stack->element_size);

    newNode->next = stack->top;
    stack->top = newNode;

    stack->size++;

    return true;
}

bool stack_pop(Stack* stack, void* output_buffer) {
    if (stack_is_empty(stack) || output_buffer == NULL) {
        return false;
    }

    Node* nodeTop = stack->top;
    memcpy(output_buffer,nodeTop->data,stack->element_size);

    stack->top = nodeTop->next;

    free(nodeTop->data);
    free(nodeTop);

    stack->size--;
    return true;
}

bool stack_peek(const Stack* stack, void* output_buffer) {
    if (stack_is_empty(stack) || output_buffer == NULL) {
        return false;
    }

    memcpy(output_buffer,stack->top->data,stack->element_size);

    return true;
}

bool stack_is_empty(const Stack* stack) {
    if (stack == NULL) {
        return true;
    }

    return stack->top == NULL;
}

size_t get_stack_size(const Stack* stack) {
    if (stack == NULL) {
        return 0;
    }

    return stack->size;
}

