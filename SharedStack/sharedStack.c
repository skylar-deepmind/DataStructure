//
// Created by Skylar X on 2025/9/3.
//
#include "sharedStack.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct SharedStack {
    void *data;
    int top_1;
    int top_2;
    size_t capacity;
    size_t element_size;
};

Stack *stack_create(size_t total_capacity, size_t element_size) {
    if (total_capacity == 0 || element_size == 0) {
        printf("Invalid parameters!!!");
        return NULL;
    }

    Stack *stack = (Stack *) malloc(sizeof(Stack));
    if (stack == NULL) {
        printf("Failed to allocated to the stack!!!");
        return NULL;
    }

    stack->data = malloc(stack->element_size);
    if (stack->data == NULL) {
        printf("Failed to allocated to the data!!!");
        return NULL;
    }

    stack->capacity = total_capacity;
    stack->element_size = element_size;
    stack->top_1 = -1;
    stack->top_2 = (int) total_capacity;

    return stack;
}

void stack_destroy(Stack **p_stack) {
    if (p_stack == NULL || *p_stack == NULL) {
        return;
    }

    free((*p_stack)->data);
    free(*p_stack);

    *p_stack = NULL;
}

bool stack_push(Stack *stack, StackNumber stack_number, const void *element_data) {
    if (stack == NULL || stack_is_full(stack) || element_data == NULL) {
        return false;
    }

    void *target_address;
    if (stack_number == STACK_ONE) {
        stack->top_1++;
        target_address = (char *) stack->data + stack->element_size * stack->top_1;
    } else {
        stack->top_2--;
        target_address = (char *) stack->data + stack->element_size * stack->top_2;
    }

    memcpy(target_address, element_data, stack->element_size);

    return true;
}

bool stack_pop(Stack *stack, StackNumber stack_number, void *output_buffer) {
    if (stack == NULL || stack_is_empty(stack, stack_number) || output_buffer == NULL) {
        return false;
    }

    void* source_address;
    if (stack_number == STACK_ONE) {
        source_address = (char*)stack->data + stack->top_1 * stack->element_size;
        memcpy(output_buffer,source_address,stack->element_size);
        stack->top_1--;
    }else {
        source_address = (char*)stack->data + stack->top_2 * stack->element_size;
        memcpy(output_buffer,source_address,stack->element_size);
        stack->top_2++;
    }

    return true;
}

bool stack_peek(const Stack *stack, StackNumber stack_number, const void *output_buffer) {
    if (stack == NULL || stack_is_empty(stack, stack_number) || output_buffer == NULL) {
        return false;
    }

    void* source_address;
    if (stack_number == STACK_ONE) {
        source_address = (char*)stack->data + stack->top_1 * stack->element_size;
    }else {
        source_address = (char*)stack->data + stack->top_2 * stack->element_size;
    }

    memcpy(output_buffer,source_address,stack->element_size);

    return true;
} //这个和上面的三个什么时候用const有说法吗？？？

bool stack_is_full(const Stack *stack) {
    if (!stack) {
        return true;
    }

    return stack->top_1 + 1 == stack->top_2;
}

bool stack_is_empty(const Stack *stack, StackNumber stack_number) {
    if (!stack) {
        return true;
    }

    if (stack_number == STACK_ONE) {
        return stack->top_1 == -1;
    } else {
        return stack->top_2 == (int) stack->capacity;
    }
}

size_t get_stack_size(const Stack *stack, StackNumber stack_number) {
    if (stack == NULL) return 0;

    if (stack_number == STACK_ONE) {
        return (size_t)stack->top_1 + 1;
    }else {
        return stack->capacity - stack->top_2;
    }
}

size_t get_total_capacity(const Stack *stack) {
    if (stack == NULL) {
        return 0;
    }

    return stack->capacity;
}
