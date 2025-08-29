#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *list_create(int data) {
    Node *newNode = (Node *) malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("Malloc Error!");
        return NULL;
    }

    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}

void list_append(Node **headRef, int data) {
    Node *newNode = list_create(data);
    if (newNode == NULL) {
        return;
    }

    if (*headRef == NULL) {
        *headRef = newNode;
        return;
    }

    Node *lastNode = *headRef;
    while (lastNode->next != NULL) {
        lastNode = lastNode->next;
    }

    lastNode->next = newNode;
}

void list_preappend(Node **headRef, int data) {
    Node *newNode = list_create(data);
    newNode->next = *headRef; //有点晕了一个*两个*的
    *headRef = newNode;
}

void list_print(Node *headRef) {
    Node *cur = headRef;
    printf("\n当前 list ：");
    while (cur != NULL) {
        printf("%d ==> ", cur->data);
        cur = cur->next;
    }
    printf("NULL.\n");
}

Node *list_find(Node *head, int data) {
    Node *cur = head;
    while (cur != NULL) {
        if (cur->data == data) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

void list_delete(Node **headRef, int data) {
    Node *temp = *headRef;
    // Node *pre = NULL;
    Node *pre = NULL; //改成这个统一赋值也OK吧

    if (temp != NULL && temp->data == data) {
        *headRef = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->data != data) {
        pre = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        return; //不理解这个在判断什么？？？
    }

    pre->next = temp->next;
    free(temp);
}

void list_free(Node **headRef) {
    if (headRef == NULL)return;

    Node *cur = *headRef;
    Node *next;

    while (cur != NULL) {
        next = cur->next;
        free(cur);
        cur = next;
    }

    *headRef = NULL;
}

int main(void) {
    Node* head = NULL;

    list_append(&head,1);
    list_append(&head,2);
    list_append(&head,3);
    list_append(&head,4);

    list_print(head);

    list_delete(&head,3);
    list_print(head);

    // list_find(head,4);
    // list_print(head);

    list_preappend(&head,15);
    list_print(head);
}
