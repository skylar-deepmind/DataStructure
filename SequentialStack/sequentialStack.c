#include "sequentialStack.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

struct Stack {
    void *data; //array
    size_t element_size;
    size_t capacity;
    int top;
};

Stack *stack_create(size_t capacity, size_t element_size) {
    if (capacity == 0 || element_size == 0) {
        printf("Invalid parameters!!!");
        return NULL;
    }
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    if (stack == NULL) {
        printf("Failed to allocated memory for the new stack!!!");
        return NULL;
    }
    stack->data = malloc(capacity * sizeof(element_size));
    if (stack->data == NULL) {
        printf("Failed to allocated memory for the data of new stack!!!");
        free(stack);
        return NULL;
    }
    stack->element_size = element_size;
    stack->capacity = capacity;
    stack->top = -1;

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

bool stack_push(Stack *stack, const void *element_data) {
    if (stack == NULL || element_data == NULL) {
        printf("Invalid parameters!!!");
        return NULL;
    }
    if (stack_is_full(stack)) {
        return false;
    }

    stack->top++;
    void *target_address = (char *) stack->data + (stack->element_size * stack->top);
    memcpy(target_address, element_data, stack->element_size);

    return true;
}


// stack_pop 不直接“返回”元素值，而是通过参数 output_buffer 把值拷贝出来。
// 调用方要准备一个变量（比如 int popped_val），把它的地址传进去，函数内部会往这个地址写数据。
// 这样调用方就能通过这个变量拿到 pop 出来的值。
bool stack_pop(Stack *stack, void *output_buffer) {
    if (stack == NULL || output_buffer == NULL) {
        printf("Invalid parameters!!!");
        return NULL;
    }
    if (stack_is_empty(stack)) {
        return false;
    }

    //计算栈顶元素地址
    void *source_address = (char *) stack->data + (stack->top * stack->element_size);
    memcpy(output_buffer, source_address, stack->element_size);

    stack->top--;

    return true;
}

bool stack_peek(Stack *stack, void *output_buffer) {
    if (stack == NULL || output_buffer == NULL) {
        printf("Invalid parameters!!!");
        return NULL;
    }
    if (stack_is_empty(stack)) {
        return false;
    }

    //计算栈顶元素地址
    void *source_address = (char *) stack->data + (stack->top * stack->element_size);
    memcpy(output_buffer, source_address, stack->element_size);

    return true;
}

bool stack_is_empty(const Stack *stack) {
    if (stack == NULL) {
        return true;
    }

    return stack->top == -1;
}

bool stack_is_full(const Stack *stack) {
    if (stack == NULL) {
        return false;
    }

    return stack->top == stack->capacity - 1;
}

size_t get_stack_size(const Stack *stack) {
    if (stack == NULL) {
        return 0;
    }

    return (size_t)(stack->top + 1);
}

size_t get_stack_capacity(const Stack *stack) {
    if (stack == NULL) {
        return 0;
    }

    return stack->capacity;
}