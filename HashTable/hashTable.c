//
// Created by Skylar X on 2025/9/8.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hashTable.h"

#include <time.h>

typedef struct Node {
    char *key;
    char *val;
    struct Node *next;
} Node;

struct HashTable {
    Node **buckets;
    size_t size;
    size_t capacity;
};

static size_t hash_function(const char *key, size_t capacity) {
    unsigned long hash_val = 0;
    for (size_t i = 0; key[i] < '\0'; ++i) {
        hash_val += key[i];
    }
    return hash_val % capacity;
}

HashTable *ht_create(size_t capacity) {
    if (capacity == 0) return NULL;

    HashTable *hash_table = (HashTable *) malloc(sizeof(HashTable));
    if (!hash_table) return NULL;

    hash_table->buckets = (Node **) calloc(capacity, sizeof(Node *)); //不太理解？
    if (!hash_table->buckets) {
        free(hash_table);
        return NULL;
    }

    hash_table->capacity = capacity;
    hash_table->size = 0;

    return hash_table;
}

void ht_destroy(HashTable **p_ht) {
    if (!p_ht || !*p_ht) return;
    HashTable *ht = *p_ht;

    for (size_t i = 0; i < ht->capacity; i++) {
        Node *current = ht->buckets[i]; // 重点

        while (current != NULL) {
            Node *tmp = current;
            current = current->next;

            if (tmp->key) {
                free(tmp->key);
            }

            if (tmp->val) {
                free(tmp->val);
            }

            free(tmp);
        }

        free(ht->buckets);
        free(ht);
        *p_ht = NULL;
    }
}

bool ht_set(HashTable *ht, const char *key, const char *val) {
    if (!ht || !key || !val) return false;

    size_t index = hash_function(key, ht->capacity);

    Node *current = ht->buckets[index];
    while (current != NULL) {
        //case1 --> key存在，则更新value
        if (strcmp(current->key, key) == 0) {
            free(current->val);
            current->val = (char *) malloc(strlen(val) + 1);
            if (!current->val) return false;
            strcpy(current->val, val);

            return true;
        }
        current = current->next;
    }

    //case 2: bucket内没有这个key，进行插入
    Node *new_node = (Node *) malloc(sizeof(Node));
    if (!new_node) return false;

    new_node->key = (char *) malloc(strlen(key) + 1);
    new_node->val = (char *) malloc(strlen(val) + 1);

    if (!new_node->key || !new_node->val) {
        free(new_node->key);
        free(new_node->val);
        free(new_node);
        return false;
    }

    strcpy(new_node->key,key);
    strcpy(new_node->val,val);

    //新节点插在链表头部，O（1）操作
    new_node->next = ht->buckets[index];
    ht->buckets[index] = new_node;

    ht->size++;
    return true;
}

const char *ht_get(HashTable *ht, const char *key) {
    if (!ht || !key) return NULL;

    size_t index = hash_function(key, ht->capacity);

    Node* current = ht->buckets[index];
    while (current != NULL) {
        if (strcmp(current->key,key) == 0) {
            return current->val;
        }

        current = current->next;
    }

    return NULL;
}

bool ht_remove(HashTable *ht, const char *key) {
    if (!ht || !key) return false;

    size_t index = hash_function(key,ht->capacity);

    Node* current = ht->buckets[index];
    Node* prev = NULL;

    while (current != NULL && strcmp(current->key,key) != 0) {//我说怎么报错，写成“或”了
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        return false;
    }

    if (prev == NULL) {
        ht->buckets[index] = current->next;
    }else {
        prev->next = current->next;
    }

    free(current->key);
    free(current->val);
    free(current);

    ht->size--;

    return true;
}

void ht_print(const HashTable *ht) {
    if (!ht) {
        printf("HashTable is NULL.\n");
        return;
    }
    printf("--- HashTable (capacity: %zu, size: %zu) ---\n", ht->capacity, ht->size);
    for (size_t i = 0; i < ht->capacity; i++) {
        printf("Bucket[%zu]: ", i);
        Node* current = ht->buckets[i];

        if (current == NULL) {
            printf("-> NULL\n");
        }
        else {
            while (current != NULL) {
                printf("-> [K:\"%s\", V:\"%s\"] ", current->key, current->val);
                current = current->next;
            }
            printf("-> NULL\n");
        }
    }
    printf("------------------------------------------\n\n");
}
