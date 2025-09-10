//
// Created by Skylar X on 2025/9/9.
//
#pragma once
#include <stdbool.h>
#include <stddef.h>

typedef struct BST BST;

typedef int (*CompFunc)(const void* a, const void* b);

typedef void (*VisFunc)(const void* data);

typedef enum {
    IN_ORDER,
    PRE_ORDER,
    POST_ORDER
}TraverseOrder;

BST* bst_create(size_t element_size, CompFunc comp_func);

void bst_destroy(BST** p_bst);

bool bst_insert(BST* bst, const void* element_data);

bool bst_remove(BST* bst, const void* element_data);

bool bst_search(const BST* bst, const void* element_data);

void bst_traverse(const BST* bst,TraverseOrder order,VisFunc vis_func);

bool bst_is_empty(const BST* bst);

size_t bst_get_size(const BST* bst);