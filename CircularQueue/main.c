#include "circularQueue.h"

#include <stdio.h>



// 辅助函数，用于打印队列的详细内部状态，便于教学

// ... (此处省略与上一版完全相同的 print_queue_status 函数) ...

void print_queue_status(const Queue* q, const char* title) {

    printf("--- %s ---\n", title);

    if (!q) {

        printf("队列为 NULL\n\n");

        return;

    }

    printf("容量: %zu, 大小: %zu\n", get_queue_capacity(q), get_queue_size(q));

    printf("空? %s, 满? %s\n", queue_is_empty(q) ? "是" : "否", queue_is_full(q) ? "是" : "否");

    struct CircularQueue_Internal {

        void* data; size_t capacity; size_t element_size; size_t size;

        int front; int rear;

    };

    struct CircularQueue_Internal* q_internal = (struct CircularQueue_Internal*)q;

    printf("内部指针: front = %d, rear = %d\n\n", q_internal->front, q_internal->rear);

}





int main(void) {

    // 1. 创建一个容量为5的整数队列

    Queue* q = queue_create(5, sizeof(int));

    print_queue_status(q, "1. 初始状态");



    // 2. 入队3个元素

    for (int i = 10; i <= 30; i += 10) {

        printf("入队: %d\n", i);

        queue_enqueue(q, &i);

    }

    print_queue_status(q, "2. 入队 10, 20, 30 后");



    // 3. 出队2个元素

    int dequeued_val;

    for (int i = 0; i < 2; i++) {

        if (queue_dequeue(q, &dequeued_val)) {

            printf("出队: %d\n", dequeued_val);

        }

    }

    print_queue_status(q, "3. 出队两个元素后");



    // 4. 继续入队，展示“循环”特性

    struct CircularQueue_Internal {

        void* data; size_t capacity; size_t element_size; size_t size;

        int front; int rear;

    };

    printf("现在 rear=%d, front=%d。空间已在数组前方空出。\n", ((struct CircularQueue_Internal*)q)->rear, ((struct CircularQueue_Internal*)q)->front);

    printf("继续入队 40, 50, 60 来填满队列...\n");

    for (int i = 40; i <= 60; i += 10) {

        printf("入队: %d\n", i);

        queue_enqueue(q, &i);

    }

    print_queue_status(q, "4. 入队 40, 50, 60 后 (发生循环)");



    // 5. 查看队头

    int peek_val;

    if (queue_peek(q, &peek_val)) {

        printf("查看队头元素 (应为30): %d\n\n", peek_val);

    }



    // 6. 尝试在满队列时入队

    int overflow_val = 999;

    printf("尝试入队 %d 到满队列中...\n", overflow_val);

    if (!queue_enqueue(q, &overflow_val)) {

        printf("入队失败，符合预期。\n\n");

    }



    // 7. 全部出队，清空队列

    printf("将所有元素出队:\n");

    while (!queue_is_empty(q)) {

        queue_dequeue(q, &dequeued_val);

        printf("出队: %d\n", dequeued_val);

    }

    print_queue_status(q, "7. 全部出队后");



    // 8. 销毁队列

    queue_destroy(&q);

    printf("队列已销毁，指针为: %s\n", q == NULL ? "NULL" : "Not NULL");



    return 0;

}