#include <stdio.h>
#include "bst.h"

// --- 用户定义的比较和访问函数 ---

// 比较两个整数

int compare_int(const void* a, const void* b) {

    int int_a = *(const int*)a;

    int int_b = *(const int*)b;

    if (int_a < int_b) return -1;

    if (int_a > int_b) return 1;

    return 0;

}

// 打印一个整数

void visit_int(const void* data) {

    printf("%d ", *(const int*)data);

}



void print_in_order(const BST* bst) {

    printf("中序遍历 (有序): ");

    bst_traverse(bst, IN_ORDER, visit_int);

    printf("\n");

}



int main() {

    printf("--- 现代C语言泛型二叉搜索树实现 ---\n");

    BST* bst = bst_create(sizeof(int), compare_int);



    // 1. 插入节点

    printf("\n1. 插入节点: 20, 10, 30, 5, 15, 25, 40, 3, 7\n");

    int values[] = { 20, 10, 30, 5, 15, 25, 40, 3, 7 };

    for (size_t i = 0; i < sizeof(values) / sizeof(int); i++) {

        bst_insert(bst, &values[i]);

    }

    print_in_order(bst);

    printf("当前大小: %zu\n", bst_get_size(bst));



    // 2. 搜索节点

    printf("\n2. 搜索节点...\n");

    int key_to_find = 15;

    printf("搜索 %d: %s\n", key_to_find, bst_search(bst, &key_to_find) ? "找到" : "未找到");

    key_to_find = 99;

    printf("搜索 %d: %s\n", key_to_find, bst_search(bst, &key_to_find) ? "找到" : "未找到");



    // 3. 删除操作 - 情况1: 叶子节点

    printf("\n3. 删除叶子节点 (7)...\n");

    int key_to_remove = 7;

    bst_remove(bst, &key_to_remove);

    print_in_order(bst);



    // 4. 删除操作 - 情况2: 只有一个子节点的节点

    // 我们先删除 3，让 5 只有一个右子节点。然后再删除 5。

    printf("\n4. 删除只有一个子节点的节点 (5)...\n");

    key_to_remove = 3;

    bst_remove(bst, &key_to_remove); // 先删掉3

    key_to_remove = 5;

    bst_remove(bst, &key_to_remove); // 再删5，此时5应该只有一个孩子

    print_in_order(bst);



    // 5. 删除操作 - 情况3: 有两个子节点的节点

    printf("\n5. 删除有两个子节点的节点 (10)...\n");

    key_to_remove = 10;

    bst_remove(bst, &key_to_remove);

    print_in_order(bst);



    // 6. 删除根节点

    printf("\n6. 删除根节点 (20)...\n");

    key_to_remove = 20;

    bst_remove(bst, &key_to_remove);

    print_in_order(bst);

    printf("当前大小: %zu\n", bst_get_size(bst));



    // 7. 销毁树

    printf("\n7. 销毁树...\n");

    bst_destroy(&bst);

    printf("树已销毁，指针为: %s\n", bst == NULL ? "NULL" : "OK");



    return 0;

}