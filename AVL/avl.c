//
// Created by Skylar X on 2025/9/15.
//
#include "avl.h"
#include <stdlib.h>
#include <assert.h>
#include <time.h>

struct AVLNode {
    void *data;
    AVLNode *left;
    AVLNode *right;
    int height;
};

struct AVLTree {
    AVLNode *root;
    AVLCompFunc comp_func;
    AVLFreeFunc free_func;
    void *context;
    size_t size;
};

//-----------------------------------------------
//               内部函数声明 Started
//-----------------------------------------------

static AVLNode *node_create(void *data);

static void node_destroy(AVLNode *node, AVLFreeFunc free_func, void *context);

static int node_height(const AVLNode *node);

static void node_update_height(AVLNode *node);

static int node_balance_factor(const AVLNode *node);

static AVLNode *node_rotate_left(AVLNode *node);

static AVLNode *node_rotate_right(AVLNode *node);

static AVLNode *node_balance(AVLNode *node);

static AVLNode *node_insert(AVLNode *node, void *data, AVLCompFunc comp_func, void *context, bool *inserted);

static AVLNode *node_delete(AVLNode *node, const void *data, AVLCompFunc comp_func, void *context,
                            AVLFreeFunc free_func,bool *deleted);

static AVLNode *node_find_min(AVLNode *node);

static void *node_find(const AVLNode *node, const void *data, AVLCompFunc comp_func, void *context);

static void node_traverse_inorder(const AVLNode *node, AVLTraverseFunc traverse_func, void *context);

static void node_traverse_preorder(const AVLNode *node, AVLTraverseFunc traverse_func, void *context);

static void node_traverse_postorder(const AVLNode *node, AVLTraverseFunc traverse_func, void *context);

static bool node_validate(const AVLNode *node, AVLCompFunc comp_func, void *context, const void *min, const void *max);

//-----------------------------------------------
//               内部函数声明 Ended
//-----------------------------------------------

AVLTree *avl_create(AVLCompFunc comp_func, AVLFreeFunc free_func, void *context) {
    assert(comp_func != NULL);

    AVLTree *tree = (AVLTree *) malloc(sizeof(AVLTree));
    if (tree == NULL) return NULL;

    tree->root = NULL;
    tree->comp_func = comp_func;
    tree->free_func = free_func;
    tree->context = context;
    tree->size = 0;

    return tree;
}

void avl_destroy(AVLTree *tree) {
    if (tree == NULL) return;

    node_destroy(tree->root, tree->free_func, tree->context);

    free(tree);
}

bool avl_insert(AVLTree *tree, void *data) {
    assert(tree != NULL);
    assert(data != NULL);

    bool inserted = false;
    tree->root = node_insert(tree->root, data, tree->comp_func, tree->context, &inserted);

    if (inserted) tree->size++;

    return inserted;
}

bool avl_delete(AVLTree *tree, const void *data) {
    assert(tree != NULL);
    assert(data != NULL);

    bool deleted = false;
    tree->root = node_delete(tree->root, data, tree->comp_func, tree->context, tree->free_func, &deleted);

    if (deleted) {
        tree->size--;
    }

    return deleted;
}

void *avl_find(AVLTree *tree, const void *data) {
    assert(tree != NULL);
    assert(data != NULL);

    return node_find(tree->root, data, tree->comp_func, tree->context);
}

bool avl_update(AVLTree *tree, const void *old_data, const void *new_data) {
    assert(tree != NULL);
    assert(old_data != NULL);
    assert(new_data != NULL);

    if (tree->comp_func(old_data, new_data, tree->context) == 0) {
        return true;
    }

    if (avl_find(tree, old_data) == NULL) {
        return false;
    }

    avl_delete(tree, old_data);

    return avl_insert(tree, new_data);
}

size_t avl_size(const AVLTree *tree) {
    if (tree == NULL) return 0;

    return tree->size;
}

bool avl_is_empty(const AVLTree *tree) {
    if (tree == NULL) return true;

    return tree->size == 0;
}

void avl_traverse_inorder(const AVLTree *tree, AVLTraverseFunc traverse_func, void *context) {
    assert(tree != NULL);
    assert(traverse_func != NULL);

    node_traverse_inorder(tree->root, traverse_func, tree->context);
}

void avl_traverse_preorder(const AVLTree *tree, AVLTraverseFunc traverse_func, void *context) {
    assert(tree != NULL);
    assert(traverse_func != NULL);

    node_traverse_preorder(tree->root, traverse_func, tree->context);
}

void avl_traverse_postorder(const AVLTree *tree, AVLTraverseFunc traverse_func, void *context) {
    assert(tree != NULL);
    assert(traverse_func != NULL);

    node_traverse_postorder(tree->root, traverse_func, tree->context);
}

int avl_height(const AVLTree *tree) {
    assert(tree != NULL);
    return node_height(tree->root);
}

bool avl_validate(const AVLTree *tree) {
    assert(tree != NULL);
    return node_validate(tree->root, tree->comp_func, tree->context,NULL,NULL);
}


//-----------------------------------------------
//               内部函数实现 Started
//-----------------------------------------------

static AVLNode *node_create(void *data) {
    AVLNode *node = (AVLNode *) malloc(sizeof(AVLNode));

    if (node == NULL) {
        return NULL;
    }

    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;

    return node;
}

static void node_destroy(AVLNode *node, AVLFreeFunc free_func, void *context) {
    if (node == NULL) {
        return;
    }

    node_destroy(node->left, free_func, context);
    node_destroy(node->right, free_func, context);

    if (free_func != NULL) {
        free_func(node->data, context);
    }

    free(node);
}

static int node_height(const AVLNode *node) {
    return node ? node->height : 0;
}

static void node_update_height(AVLNode *node) {
    if (node == NULL) {
        return;
    }

    int left_height = node_height(node->left);
    int right_height = node_height(node->right);

    node->height = 1 + (left_height > right_height ? left_height : right_height);
}

static int node_balance_factor(const AVLNode *node) {
    return node ? node_height(node->left) - node_height(node->right) : 0;
}

static AVLNode *node_rotate_left(AVLNode *node) {
    assert(node != NULL);
    assert(node->right != NULL);

    AVLNode *new_root = node->right;
    node->right = new_root->left;

    node_update_height(node);
    node_update_height(new_root);

    return new_root;
}

static AVLNode *node_rotate_right(AVLNode *node) {
    assert(node != NULL);
    assert(node->left != NULL);

    AVLNode *new_root = node->left;
    node->left = new_root->right;

    node_update_height(node);
    node_update_height(new_root);

    return new_root;
}

static AVLNode *node_balance(AVLNode *node) {
    if (node == NULL) return NULL;

    node_update_height(node);
    int balance = node_balance_factor(node);

    if (balance > 1) {
        if (node_balance_factor(node->left) < 0) {
            node->left = node_rotate_left(node->left);
        }

        return node_rotate_right(node);
    }

    if (balance < -1) {
        if (node_balance_factor(node->right) > 0) {
            node->right = node_rotate_right(node->right);
        }

        return node_rotate_left(node);
    }

    return node;
}

static AVLNode *node_insert(AVLNode *node, void *data, AVLCompFunc comp_func, void *context, bool *inserted) {
    if (node == NULL) {
        *inserted = true;
        return node_create(data);
    }

    int cmp = comp_func(data, node->data, context);

    if (cmp < 0) {
        node->left = node_insert(node->left, data, comp_func, context, inserted);
    } else if (cmp > 0) {
        node->right = node_insert(node->right, data, comp_func, context, inserted);
    } else {
        *inserted = false;
        return node;
    }

    return node_balance(node);
}

static AVLNode *node_delete(AVLNode *node, const void *data, AVLCompFunc comp_func, void *context,
                            AVLFreeFunc free_func,bool *deleted) {
    if (node == NULL) {
        *deleted = false;
        return NULL;
    }

    int cmp = comp_func(data, node->data, context);

    if (cmp < 0) {
        node->left = node_delete(node->left, data, comp_func, context, free_func, deleted);
    } else if (cmp > 0) {
        node->right = node_delete(node->right, data, comp_func, context, free_func, deleted);
    } else {
        *deleted = true;

        if (node->left == NULL || node->right == NULL) {
            AVLNode *tmp = node->left ? node->left : node->right;

            if (free_func != NULL) {
                free_func(node->data, context);
            }

            free(node);

            return tmp;
        } else {
            AVLNode *min_right = node_find_min(node->right);

            void *tmp_data = node->data;
            node->data = min_right->data;
            min_right->data = tmp_data;

            node->right = node_delete(node->right, data, comp_func, context, free_func, deleted);
        }
    }

    return node_balance(node);
}

static AVLNode *node_find_min(AVLNode *node) {
    while (node != NULL && node->left != NULL) {
        node = node->left;
    }

    return node;
}

static void *node_find(const AVLNode *node, const void *data, AVLCompFunc comp_func, void *context) {
    if (node == NULL) return NULL;

    int cmp = comp_func(data, node->data, context);

    if (cmp < 0) {
        return node_find(node->left, data, comp_func, context);
    } else if (cmp > 0) {
        return node_find(node->right, data, comp_func, context);
    } else {
        return node->data;
    }
}

static void node_traverse_inorder(const AVLNode *node, AVLTraverseFunc traverse_func, void *context) {
    if (node == NULL) return;

    node_traverse_inorder(node->left, traverse_func, context);
    traverse_func(node->data, context);
    node_traverse_inorder(node->right, traverse_func, context);
}

static void node_traverse_preorder(const AVLNode *node, AVLTraverseFunc traverse_func, void *context) {
    if (node == NULL) return;

    traverse_func(node->data, context);
    node_traverse_preorder(node->left, traverse_func, context);
    node_traverse_preorder(node->right, traverse_func, context);
}

static void node_traverse_postorder(const AVLNode *node, AVLTraverseFunc traverse_func, void *context) {
    if (node == NULL) return;

    node_traverse_postorder(node->left,traverse_func,context);
    node_traverse_postorder(node->right,traverse_func,context);
    traverse_func(node->data,context);
}

static bool node_validate(const AVLNode *node, AVLCompFunc comp_func, void *context, const void *min, const void *max) {
    if (node == NULL) {

        return true;

    }



    // 检查BST性质

    if (min != NULL && comp_func(node->data, min, context) <= 0) {

        return false;

    }

    if (max != NULL && comp_func(node->data, max, context) >= 0) {

        return false;

    }



    // 检查平衡因子

    int balance = node_balance_factor(node);

    if (balance < -1 || balance > 1) {

        return false;

    }



    // 检查高度是否正确

    int expected_height = 1 + (node_height(node->left) > node_height(node->right) ?

        node_height(node->left) : node_height(node->right));

    if (node->height != expected_height) {

        return false;

    }



    // 递归检查子树

    return node_validate(node->left, comp_func, context, min, node->data) &&

        node_validate(node->right, comp_func, context, node->data, max);
}

//-----------------------------------------------
//               内部函数实现 Ended
//-----------------------------------------------
