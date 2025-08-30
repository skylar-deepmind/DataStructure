#pragma once
#include <stdbool.h>

//这是一个音乐播放器的模拟
//使用双向链表的数据结构
//有一个双向链表的管理器，管理size，head，tail
//节点内容包含歌曲（歌曲结构体里面包含歌曲相关的信息），prev和next的指针相当于“上一曲”“下一曲”的功能模拟
typedef struct Song {
    char* title;
    char* artist;
    int duration;
}Song;

typedef struct Node{
    Song data;
    struct Node* next;
    struct Node* prev;
}Node;

typedef struct DoublyLinkedList{
    Node* head;
    Node* tail;
    int size;
} DoublyLinkedList;

DoublyLinkedList* list_create();

void list_free(DoublyLinkedList* list);

bool list_append(DoublyLinkedList* list,Song songData);

bool list_prepend(DoublyLinkedList* list,Song songData);

bool list_insert(DoublyLinkedList* list, Node* targetNode, Song songData);

bool list_delete(DoublyLinkedList* list, Node* NodeToDelete);

Node* find_by_title(const DoublyLinkedList* list,const char* title);

void list_print_forward(const DoublyLinkedList* list);

void list_print_backward(const DoublyLinkedList* list);