//
// Created by Skylar X on 2025/9/9.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

#include <time.h>

typedef struct Node {
    void *data;
    struct Node *left;
    struct Node *right;
} Node;

struct BST {
    Node *root;
    size_t element_size;
    size_t size;
    CompFunc comp_func;
};

static Node *_create_node(const void *data, size_t element_size) {
    if (!data || !element_size) {
        return NULL;
    }
    Node *new_node = (Node *) malloc(sizeof(Node));
    if (!new_node)return NULL;

    new_node->data = malloc(element_size);
    if (!new_node->data) {
        free(new_node);
        return NULL;
    }

    memcpy(new_node->data, data, element_size);
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

static void _destroy_recursive(Node *node) {
    if (node == NULL) return;
    _destroy_recursive(node->left);
    _destroy_recursive(node->right);
    free(node->data);
    free(node);
}

static Node *_insert_recursive(BST *bst, Node *node, const void *data) {
    if (node == NULL) {
        bst->size++;
        return _create_node(data, bst->element_size);
    }

    int cmp = bst->comp_func(data, node->data);

    if (cmp < 0) {
        node->left = _insert_recursive(bst, node->left, data);
    } else {
        node->right = _insert_recursive(bst, node->right, data);
    }

    return node;
}

//查找子树中最小的节点，用于删除操作
static Node *_find_min_recursive(Node *node) {
    while (node && node->left) {
        node = node->left;
    }

    return node;
}

static Node *_remove_recursive(BST *bst, Node *node, const void *key) {
    if (node == NULL) return NULL;

    int cmp = bst->comp_func(key, node->data);

    if (cmp < 0) {
        node->left = _remove_recursive(bst, node->left, key); //????
    } else if (cmp > 0) {
        node->right = _remove_recursive(bst, node->right, key);
    } else {
        //此时已找到
        if (node->left == NULL && node->right == NULL) {
            bst->size--;
            free(node->data);
            free(node);
            return NULL;
        }

        if (node->left == NULL) {
            bst->size--;
            Node *tmp = node->right;
            free(node->data);
            free(node);
            return tmp;
        } else if (node->right == NULL) {
            bst->size--;
            Node *tmp = node->left;
            free(node->data);
            free(node);
            return tmp;
        }

        Node *successor = _find_min_recursive(node->right);
        memcpy(node->data, successor->data, bst->element_size);
        node->right = _remove_recursive(bst, node->right, successor->data);
    }
    return node;
}

//基础理解的还不是很好
static void _traverse_recursive(const Node *node, VisFunc vis_func, TraverseOrder order) {
    if (node == NULL) return;
    if (order == PRE_ORDER) vis_func(node->data);
    _traverse_recursive(node->left, vis_func, order);
    if (order == IN_ORDER) vis_func(node->data);
    _traverse_recursive(node->right, vis_func, order);
    if (order == POST_ORDER) vis_func(node->data);
}

BST *bst_create(size_t element_size, CompFunc comp_func) {
    if (!element_size || !comp_func) return NULL;

    BST *bst = (BST *) malloc(sizeof(BST));
    if (!bst) return NULL;

    bst->root = NULL;
    bst->comp_func = comp_func;
    bst->element_size = element_size;
    bst->size = 0;

    return bst;
}

void bst_destroy(BST **p_bst) {
    if (p_bst && *p_bst) {
        _destroy_recursive((*p_bst)->root);
        free(*p_bst);
        *p_bst = NULL;
    }
}

bool bst_insert(BST *bst, const void *element_data) {
    if (!bst || !element_data) return false;

    size_t old_size = bst->size;
    bst->root = _insert_recursive(bst, bst->root, element_data);

    return old_size < bst->size;
}

bool bst_remove(BST *bst, const void *element_data) {
    if (!bst || !element_data) return false;

    size_t old_size = bst->size;
    bst->root = _remove_recursive(bst, bst->root, element_data);

    return old_size > bst->size;
}

bool bst_search(const BST *bst, const void *element_data) {
    if (!bst || !element_data) return false;
    Node *current = bst->root;

    while (current != NULL) {
        int cmp = bst->comp_func(element_data, current->data);
        if (cmp == 0) return true;
        if (cmp < 0) current = current->left;
        else current = current->right;
    }

    return false;
}

void bst_traverse(const BST *bst, TraverseOrder order, VisFunc vis_func) {
    if (bst && vis_func) {
        _traverse_recursive(bst->root, vis_func, order);
    }
}

bool bst_is_empty(const BST *bst) {
    if (!bst) return true;

    return bst->size == 0;
}

size_t bst_get_size(const BST *bst) {
    if (!bst) return 0;

    return bst->size;
}
