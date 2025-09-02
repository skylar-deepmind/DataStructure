#include <stdio.h>

#include "sequentialStack.h"

// 顺序栈



// 定义一个自定义结构体，用于测试

typedef struct {

    int id;

    double value;

} DataPoint;



// 用于打印 DataPoint 的辅助函数

void print_datapoint(const DataPoint* dp) {

    if (dp) {

        printf("DataPoint(id: %d, value: %.2f)", dp->id, dp->value);

    }

}



// --- 测试函数 ---



void test_int_stack() {

    printf("--- Testing Integer Stack ---\n");

    Stack* int_stack = stack_create(5, sizeof(int));



    if (!int_stack) {

        printf("Failed to create integer stack.\n");

        return;

    }



    printf("Stack created. Capacity: %zu, Is empty? %s\n",

        get_stack_capacity(int_stack), stack_is_empty(int_stack) ? "Yes" : "No");



    for (int i = 10; i <= 50; i += 10) {

        printf("Pushing %d... ", i);

        if (stack_push(int_stack, &i)) {

            printf("Success. Current size: %zu\n", get_stack_size(int_stack));

        }

    }

    printf("Is stack full? %s\n", stack_is_full(int_stack) ? "Yes" : "No");



    int top_val;

    if (stack_peek(int_stack, &top_val)) {

        printf("Peek at top: %d\n", top_val);

    }



    printf("Popping all elements:\n");

    while (!stack_is_empty(int_stack)) {

        int popped_val;

        if (stack_pop(int_stack, &popped_val)) {

            printf("Popped: %d\n", popped_val);

        }

    }



    printf("Is stack empty now? %s\n", stack_is_empty(int_stack) ? "Yes" : "No");



    // 销毁栈

    stack_destroy(&int_stack);

    printf("Stack destroyed. Pointer is now %s\n", int_stack == NULL ? "NULL" : "Not NULL");

    printf("\n");

}



void test_struct_stack() {

    printf("--- Testing Struct (DataPoint) Stack ---\n");

    Stack* dp_stack = stack_create(3, sizeof(DataPoint));



    DataPoint p1 = { 101, 99.5 };

    DataPoint p2 = { 102, 120.75 };

    DataPoint p3 = { 103, 85.0 };



    printf("Pushing "); print_datapoint(&p1); printf("...\n");

    stack_push(dp_stack, &p1);

    printf("Pushing "); print_datapoint(&p2); printf("...\n");

    stack_push(dp_stack, &p2);

    printf("Pushing "); print_datapoint(&p3); printf("...\n");

    stack_push(dp_stack, &p3);



    printf("Stack size: %zu, Is full? %s\n", get_stack_size(dp_stack), stack_is_full(dp_stack) ? "Yes" : "No");



    DataPoint peeked_dp;

    if (stack_peek(dp_stack, &peeked_dp)) {

        printf("Peek at top: ");

        print_datapoint(&peeked_dp);

        printf("\n");

    }



    printf("Popping all elements:\n");

    while (!stack_is_empty(dp_stack)) {

        DataPoint popped_dp;

        if (stack_pop(dp_stack, &popped_dp)) {

            printf("Popped: ");

            print_datapoint(&popped_dp);

            printf("\n");

        }

    }



    stack_destroy(&dp_stack);

    printf("Struct stack destroyed.\n\n");

}



int main() {

    test_int_stack();

    test_struct_stack();



    return 0;

}