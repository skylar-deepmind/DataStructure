//
// Created by Skylar X on 2025/9/15.
//

#pragma once
#include <stdbool.h>
#include <stddef.h>

typedef struct AVLNode AVLNode;

typedef struct AVLTree AVLTree;

typedef int (*AVLCompFunc)(const void *a, const void *b, void *context);

typedef void (*AVLTraverseFunc)(void *data, void *context);

typedef void (*AVLFreeFunc)(void *data, void *context);

AVLTree *avl_create(AVLCompFunc comp_func, AVLFreeFunc free_func, void *context);

void avl_destroy(AVLTree *tree);

bool avl_insert(AVLTree *tree, void *data);

bool avl_delete(AVLTree *tree, const void *data);

void *avl_find(AVLTree *tree, const void *data);

bool avl_update(AVLTree *tree, const void *old_data, const void *new_data);

size_t avl_size(const AVLTree *tree);

bool avl_is_empty(const AVLTree *tree);

void avl_traverse_inorder(const AVLTree *tree, AVLTraverseFunc traverse_func, void *context);

void avl_traverse_preorder(const AVLTree *tree, AVLTraverseFunc traverse_func, void *context);

void avl_traverse_postorder(const AVLTree *tree, AVLTraverseFunc traverse_func, void *context);

int avl_height(const AVLTree *tree);

bool avl_validate(const AVLTree *tree);
