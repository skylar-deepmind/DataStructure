#pragma once
#include <stddef.h>
#include <stdbool.h>

typedef struct LinkedStack Stack;

Stack* stack_create(size_t element_size);

void stack_destroy(Stack** p_stack);

bool stack_push(Stack* stack,const void* element_data);

bool stack_pop(Stack* stack, void* output_buffer);

bool stack_peek(const Stack* stack, void* output_buffer);

bool stack_is_empty(const Stack* stack);

size_t get_stack_size(const Stack* stack);