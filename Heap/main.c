#include <stdio.h>

#include "heap.h" // 包含我们的堆ADT头文件



int main() {

    printf("========== Heap ADT Demonstration ==========\n");



    // 1. 创建一个初始容量为5的堆

    printf("\n--- 1. Creating a heap with initial capacity 5 ---\n");

    Heap* my_heap = heap_create(5);

    if (!my_heap) {

        fprintf(stderr, "Failed to create heap. Exiting.\n");

        return 1;

    }

    heap_print_debug(my_heap);



    // 2. 插入一些元素

    printf("\n--- 2. Inserting elements ---\n");

    int elements[] = { 30, 80, 50, 20, 90, 10, 60, 40, 70, 100 };

    size_t num_elements = sizeof(elements) / sizeof(elements[0]);



    for (size_t i = 0; i < num_elements; ++i) {

        printf("Inserting %d...\n", elements[i]);

        heap_insert(my_heap, elements[i]);

        heap_print_debug(my_heap);

    }



    printf("\nFinal heap size: %zu\n", heap_size(my_heap));



    // 3. 查看堆顶元素

    printf("\n--- 3. Peeking at the maximum element ---\n");

    Item max_val;

    if (heap_peek(my_heap, &max_val) == 0) {

        printf("The maximum element (peek) is: %d\n", max_val);

    }

    heap_print_debug(my_heap); // 确认堆未改变



    // 4. 提取所有元素（堆排序的过程）

    printf("\n--- 4. Extracting all elements in order ---\n");

    while (!is_heap_empty(my_heap)) {

        Item extracted_val;

        if (heap_extract_max(my_heap, &extracted_val) == 0) {

            printf("Extracted max: %d. ", extracted_val);

            printf("Heap state after extraction: ");

            heap_print_debug(my_heap);

        }

    }



    printf("\nHeap is now empty.\n");

    heap_print_debug(my_heap);





    // 5. 销毁堆

    printf("\n--- 5. Destroying the heap ---\n");

    heap_destroy(&my_heap);

    if (my_heap == NULL) {

        printf("Heap destroyed successfully. my_heap pointer is now NULL.\n");

    }



    printf("\n========== Demonstration Finished ==========\n");



    return 0;

}