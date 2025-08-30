//
// Created by Skylar X on 2025/8/30.
//
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "DoublyLinkedList.h"
//这种静态方法还不理解
static Node* createNode(Song songData) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    if (!newNode) {
        printf("Failed to allocate memory for the newNode!!!");
        return NULL;
    }
    newNode->data.artist = (char *) malloc(sizeof(strlen(songData.artist)) + 1);
    newNode->data.title = (char *) malloc(sizeof(strlen(songData.title)) + 1);

    if (!newNode->data.artist || !newNode->data.title) {
        printf("Failed to allocate memory for the songData!!!");
        free(newNode->data.artist);
        free(newNode->data.title);
        free(newNode);
        return NULL;
    }

    // newNode->data.artist = songData.artist;
    // newNode->data.title = songData.title;这么写没有/0是吗？？？
    strcpy(newNode->data.artist, songData.artist);
    strcpy(newNode->data.title, songData.title);
    newNode->data.duration = songData.duration;

    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode;
}

DoublyLinkedList *list_create() {
    DoublyLinkedList *list = (DoublyLinkedList *) malloc(sizeof(DoublyLinkedList));

    if (!list) {
        printf("fail to allocate memory for new list!!!");
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;
}

void list_free(DoublyLinkedList *list) {
    if (!list) {
        printf("The list is empty, nothing to free.");
        return;
    }

    Node *current = list->head;

    while (current != NULL) {
        Node *nextNode = current->next;
        free(current->data.artist);
        free(current->data.title);
        free(current);
        current = nextNode;
    }
    free(list);
}

bool list_append(DoublyLinkedList *list, Song songData) {
    if (!list) {
        perror("List is NULL, cannot append.");
        return false; // 链表为空
    }

    Node *newNode = createNode(songData);

    if (!newNode) {
        return false;
    }

    if (list->head == NULL) {
        //链表为空
        list->head = newNode;
        list->tail = newNode;
    } else {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }

    list->size++;

    return true;
}

bool list_prepend(DoublyLinkedList *list, Song songData) {
    if (!list) {
        perror("List is NULL, cannot prepend.");
        return false; // 链表为空
    }

    Node *newNode = createNode(songData);

    if (!newNode) {
        return false;
    }

    if (list->head == NULL) {
        //链表为空
        list->head = newNode;
        list->tail = newNode;
    } else {
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
    }

    list->size++;

    return true;
}

bool list_insert(DoublyLinkedList *list, Node *targetNode, Song songData) {
    if (!list || !targetNode) {
        perror("List or targerNode is NULL, cannot prepend.");
        return false; // 链表为空
    }

    Node *newNode = createNode(songData);

    if (!newNode) {
        return false;
    }

    newNode->next = targetNode->next;
    newNode->prev = targetNode;

    if (targetNode->next != NULL) {
        targetNode->next->prev = newNode;
    } else {
        list->tail = newNode;
    }

    targetNode->next = newNode;
    list->size++;

    return true;
}

bool list_delete(DoublyLinkedList *list, Node *nodeToDelete) {
    if (!list || !nodeToDelete) {
        perror("List or node to delete is NULL.");
        return false; // 链表为空
    }

    if (nodeToDelete->prev != NULL) {
        nodeToDelete->prev->next = nodeToDelete->next;
    } else {
        list->head = nodeToDelete->next;
    }

    if (nodeToDelete->next != NULL) {
        nodeToDelete->next->prev = nodeToDelete->prev;
    } else {
        list->tail = nodeToDelete->prev;
    }

    free(nodeToDelete->data.artist);
    free(nodeToDelete->data.title);
    free(nodeToDelete);

    list->size--;

    return true;
}

Node *find_by_title(const DoublyLinkedList *list, const char *title) {
    if (!list || !title) {
        printf("List or title is NULL, cannot find.");
        return NULL;
    }

    Node *current = list->head;
    while (current != NULL) {
        if (strcmp(current->data.title, title) == 0) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

void list_print_forward(const DoublyLinkedList *list) {
    if (!list || !list->head) {
        printf("The list is empty!!!");
        return;
    }

    printf("---Playlist (Size: %d, Forward) ---\n", list->size);

    Node *current = list->head;
    int index = 1;
    while (current != NULL) {
        printf("%d. Title: %s, Artist: %s, Duration: %d seconds\n",
               index++, current->data.title, current->data.artist, current->data.duration);
        current = current->next; // 移动到下一个节点
    }
    printf("--- End of Playlist ---\n");
}

void list_print_backward(const DoublyLinkedList *list) {
    if (!list || !list->tail) {
        printf("List is empty.\n");
        return; // 链表为空
    }

    printf("---Playlist (Size: %d, Backward) ---\n", list->size);
    Node* current = list->tail;
    int index = list->size;
    while (current != NULL) {
        printf("%d. Title: %s, Artist: %s, Duration: %d seconds\n",
            index--, current->data.title, current->data.artist, current->data.duration);
        current = current->prev; // 移动到下一个节点
    }
    printf("--- End of Playlist ---\n");
}
