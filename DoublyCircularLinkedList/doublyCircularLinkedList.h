#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
}Node;

Node* list_create(int data);

void list_destroy(Node** head);

void list_insert(Node** head,Node* position, int data);

void list_delete(Node** head, Node* position);

void list_prepend(Node** head,int data);

void list_append(Node** head, int data);

void list_print(const Node* head);