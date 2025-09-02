#include <stdio.h>
#include <stdlib.h>
#include "doublyCircularLinkedList.h"


Node* list_create(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) {
        printf("Allocate memory Error!!!");
        return NULL;
    }
    node->data = data;
    node->next = node;
    node->prev = node;

    return node;
}

void list_destroy(Node** head) {
    if (!*head || !head) {
        return;
    }
    Node* current = *head;
    do {
        Node *tempNode = current;
        current = current->next;
        free(tempNode);
    }while (current != *head);

    // free(head);
    // head = NULL;//这两个 怎么用？
    *head = NULL;
}

void list_insert(Node** head,Node* position, int data) {
    if (!head || !*head || !position) {
        return;
    }

    Node* node = list_create(data);

    node->prev = position->prev;
    node->next = position;
    position->prev->next = node;
    position->prev = node;
    //都处理完了，考虑一下这个
    if (position == *head) {
        *head = node;
    }
}

void list_delete(Node** head, Node* position) {
    if (!head || !*head || !position) {
        return;
    }
    if (position->next == position) {
        *head = NULL;
    }else {
        position->prev->next = position->next;
        position->next->prev = position->prev;

        if (position == *head) {
            *head = position->next;
        }
    }
    free(position);
}

void list_prepend(Node** head,int data) {
    Node* node = list_create(data);
    if (*head == NULL) {//判断二级指针head是否为空
        *head = node;
    }else {
        Node* tail = (*head)->prev;
        node->next = *head;
        node->prev = tail;
        tail->next = node;
        (*head)->prev = node;
        *head = node;
    }
}

void list_append(Node** head, int data){
    Node* node = list_create(data);
    if (*head == NULL) {
        *head = node;
    }else {
        Node* tail = (*head)->prev;
        node->prev = tail;
        node->next = *head;
        (*head)->next = node;
        tail->next = node;
        // tail->next = node;
        // node->prev = tail;
        // node->next = *head;
        // (*head)->next = node;

    }
}

void list_print(const Node* head) {
    if (head == NULL) {
        printf("The list is Empty!!!\n");
        return;
    }
    const Node* current = head;
    printf("[ ");
    do {
        printf("%d ", current->data);
        current = current->next;
    } while (current != head);
    printf("]\n");
}
