// main.c



#include "linkedQueue.h"

#include <stdio.h>



// 定义一个结构体用于测试

typedef struct {

    int id;

    char name[16];

} Person;



void print_person(const Person* p) {

    if (p) printf("Person(id: %d, name: \"%s\")", p->id, p->name);

}



void print_queue_status(const Queue* q, const char* title) {

    printf("--- %s ---\n", title);

    if (!q) {

        printf("队列为 NULL\n\n");

        return;

    }

    printf("大小: %zu, 空? %s\n", get_queue_size(q), queue_is_empty(q) ? "是" : "否");



    Person peeked_person;

    if (queue_peek(q, &peeked_person)) {

        printf("队头是: ");

        print_person(&peeked_person);

        printf("\n");

    }

    else {

        printf("队头为空。\n");

    }

    printf("\n");

}





int main() {

    // 1. 创建一个Person类型的链式队列

    Queue* q = queue_create(sizeof(Person));

    print_queue_status(q, "1. 初始状态");



    // 2. 入队第一个元素

    Person p1 = { 101, "Alice" };

    printf("入队: "); print_person(&p1); printf("\n");

    queue_enqueue(q, &p1);

    print_queue_status(q, "2. 入队第一个元素后");



    // 3. 入队更多元素

    Person p2 = { 102, "Bob" };

    Person p3 = { 103, "Charlie" };

    printf("入队: "); print_person(&p2); printf("\n");

    queue_enqueue(q, &p2);

    printf("入队: "); print_person(&p3); printf("\n");

    queue_enqueue(q, &p3);

    print_queue_status(q, "3. 继续入队后");



    // 4. 出队一个元素

    Person dequeued_person;

    if (queue_dequeue(q, &dequeued_person)) {

        printf("出队成功: ");

        print_person(&dequeued_person);

        printf("\n");

    }

    print_queue_status(q, "4. 出队一个元素后");



    // 5. 全部出队，测试队列变空的逻辑

    printf("将所有剩余元素出队...\n");

    while (!queue_is_empty(q)) {

        if (queue_dequeue(q, &dequeued_person)) {

            printf("出队: ");

            print_person(&dequeued_person);

            printf("\n");

        }

    }

    print_queue_status(q, "5. 全部出队后");



    // 6. 尝试对空队列进行操作

    printf("尝试对空队列出队...\n");

    if (!queue_dequeue(q, &dequeued_person)) {

        printf("出队失败，符合预期。\n\n");

    }



    // 7. 销毁队列

    queue_destroy(&q);

    printf("队列已销毁，指针为: %s\n", q == NULL ? "NULL" : "Not NULL");



    return 0;

}