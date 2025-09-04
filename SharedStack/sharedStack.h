//
// Created by Skylar X on 2025/9/3.
//

#pragma once

#include <stddef.h>
#include <stdbool.h>

typedef enum {
    STACK_ONE = 1,
    STACK_TWO = 2
} StackNumber;

typedef struct SharedStack Stack;

Stack *stack_create(size_t total_capacity, size_t element_size);

void stack_destroy(Stack **p_stack);

bool stack_push(Stack *stack, StackNumber stack_number, const void *element_data);

bool stack_pop(Stack *stack, StackNumber stack_number, void *output_buffer);

bool stack_peek(const Stack *stack, StackNumber stack_number, const void *output_buffer); //这个和上面的三个什么时候用const有说法吗？？？

bool stack_is_full(const Stack *stack);

bool stack_is_empty(const Stack *stack, StackNumber stack_number);

size_t get_stack_size(const Stack *stack, StackNumber stack_number);

size_t get_total_capacity(const Stack *stack);
