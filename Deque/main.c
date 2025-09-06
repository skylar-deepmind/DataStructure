#include "deque.h"

#include <stdio.h>



void test_deque_as_queue() {

    printf("--- 1. 使用双端队列模拟“标准队列” ---\n");

    printf("(操作: push_back + pop_front)\n");



    Deque* dq = deque_create(5, sizeof(int));

    int val;



    printf("Push Back: 10, 20, 30\n");

    for (val = 10; val <= 30; val += 10) deque_push_back(dq, &val);



    printf("当前大小: %zu\n", get_deque_size(dq));



    printf("Pop Front (应按FIFO顺序):\n");

    while (!deque_is_empty(dq)) {

        deque_pop_front(dq, &val);

        printf(" -> %d\n", val);

    }

    printf("\n");

    deque_destroy(&dq);

}



void test_deque_as_stack() {

    printf("--- 2. 使用双端队列模拟“栈” ---\n");

    printf("(操作: push_front + pop_front)\n");



    Deque* dq = deque_create(5, sizeof(int));

    int val;



    printf("Push Front: 10, 20, 30\n");

    for (val = 10; val <= 30; val += 10) deque_push_front(dq, &val);



    printf("当前大小: %zu\n", get_deque_size(dq));



    printf("Pop Front (应按LIFO顺序):\n");

    while (!deque_is_empty(dq)) {

        deque_pop_front(dq, &val);

        printf(" -> %d\n", val);

    }

    printf("\n");

    deque_destroy(&dq);

}



void test_mixed_operations() {

    printf("--- 3. 混合操作测试 ---\n");

    Deque* dq = deque_create(5, sizeof(char));

    char val;



    // A, B

    val = 'A'; deque_push_back(dq, &val);

    val = 'B'; deque_push_back(dq, &val);

    printf("Push Back 'A', 'B'. Front: 'A', Back: 'B'\n");



    // X, A, B

    val = 'X'; deque_push_front(dq, &val);

    printf("Push Front 'X'. Front: 'X', Back: 'B'\n");



    // X, A, B, C

    val = 'C'; deque_push_back(dq, &val);

    printf("Push Back 'C'. Front: 'X', Back: 'C'\n");



    printf("当前队列大小: %zu. 内容(从头到尾): X, A, B, C\n", get_deque_size(dq));



    deque_peek_front(dq, &val);

    printf("Peek Front: %c\n", val);

    deque_peek_back(dq, &val);

    printf("Peek Back: %c\n", val);



    deque_pop_back(dq, &val);

    printf("Pop Back: %c. 剩下: X, A, B\n", val);



    deque_pop_front(dq, &val);

    printf("Pop Front: %c. 剩下: A, B\n", val);



    deque_destroy(&dq);

}





int main(void) {



    test_deque_as_queue();

    test_deque_as_stack();

    test_mixed_operations();

    return 0;

}