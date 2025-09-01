#include <stdio.h>
#include "doublyCircularLinkedList.h"

int main(void) {
    Node* list = NULL;
    list_prepend(&list,10);
    list_prepend(&list,20);
    list_prepend(&list,30);
    list_prepend(&list,40);
    list_prepend(&list,50);

    printf("初始链表: ");
    list_print(list);

    Node *pos = list->next->next; // 指向30
    list_insert(&list, pos, 25);
    printf("在30前插入25: ");
    list_print(list);

    list_delete(&list, pos); // 删除30
    printf("删除30后: ");
    list_print(list);

    list_destroy(&list);
    list_print(list);

    return 0;
}