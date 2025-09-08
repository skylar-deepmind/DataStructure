//
// Created by Skylar X on 2025/9/8.
//
#pragma once
#include <stddef.h>
#include <stdbool.h>

typedef struct HashTable HashTable;

HashTable *ht_create(size_t capacity);

void ht_destroy(HashTable **p_ht);

bool ht_set(HashTable *ht, const char *key, const char *val);

const char *ht_get(HashTable *ht, const char *key);

bool ht_remove(HashTable *ht, const char *key);

void ht_print(const HashTable *ht);
