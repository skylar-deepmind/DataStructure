#include <stdio.h>

#include <stdlib.h>

#include <string.h> // 需要 strcmp 和 strdup

#include "avl.h"



// =================================================================

// ============== 测试 1: 整数（原 main 函数内容） =================

// =================================================================



// 用于测试的比较函数（比较整数）

int compare_int(const void* a, const void* b, void* context) {

    (void)context; // context 在此示例中未使用

    int int_a = *(const int*)a;

    int int_b = *(const int*)b;

    if (int_a < int_b) return -1;

    if (int_a > int_b) return 1;

    return 0;

}



// 释放整数数据的回调函数

void free_int(void* data, void* context) {

    (void)context; // context 在此示例中未使用

    free(data);

}



// 遍历时打印整数的回调函数

void print_int(void* data, void* context) {

    (void)context; // context 在此示例中未使用

    printf("%d ", *(int*)data);

}



// 辅助函数：动态分配一个整数

int* create_int(int value) {

    int* p = (int*)malloc(sizeof(int));

    if (p) {

        *p = value;

    }

    return p;

}



void print_line() {

    printf("----------------------------------------\n");

}



void run_integer_test() {

    printf("===== Running Integer Test =====\n");

    // 创建AVL树

    AVLTree* tree = avl_create(compare_int, free_int, NULL);

    if (!tree) {

        fprintf(stderr, "Failed to create AVL tree.\n");

        return;

    }



    printf("AVL Tree created successfully.\n");

    printf("Is tree empty? %s\n", avl_is_empty(tree) ? "Yes" : "No");

    print_line();



    // --- 插入测试 ---

    printf("Inserting elements: 10, 20, 30, 40, 50, 25\n");

    int values_to_insert[] = { 10, 20, 30, 40, 50, 25 };

    for (size_t i = 0; i < sizeof(values_to_insert) / sizeof(int); ++i) {

        avl_insert(tree, create_int(values_to_insert[i]));

    }



    printf("Tree size: %zu\n", avl_size(tree));

    printf("Tree height: %d\n", avl_height(tree));

    printf("Is tree valid? %s\n", avl_validate(tree) ? "Yes" : "No");

    print_line();



    // --- 遍历测试 ---

    printf("In-order traversal:   ");

    avl_traverse_inorder(tree, print_int, NULL);

    printf("\n");



    // --- 删除测试 ---

    printf("Deleting element 40...\n");

    int key_to_delete = 40;

    avl_delete(tree, &key_to_delete);

    printf("In-order after deleting 40: ");

    avl_traverse_inorder(tree, print_int, NULL);

    printf("\n");

    printf("Is tree valid? %s\n", avl_validate(tree) ? "Yes" : "No");

    print_line();



    // --- 更新测试 ---

    printf("Updating element...\n");

    int old_key = 50;

    int* new_key_ptr = create_int(55);

    printf("Updating %d to %d...\n", old_key, *new_key_ptr);

    bool updated = avl_update(tree, &old_key, new_key_ptr);

    if (updated) {

        printf("Update successful.\n");

        printf("In-order after update: ");

        avl_traverse_inorder(tree, print_int, NULL);

        printf("\n");

    }

    else {

        printf("Update failed.\n");

        free(new_key_ptr); // 如果更新失败，需要释放新数据的内存

    }

    print_line();



    // --- 销毁测试 ---

    printf("Destroying the integer tree...\n");

    avl_destroy(tree);

    printf("Integer tree destroyed.\n");

}





// =================================================================

// ============== 测试 2: Student 类（利用 Context） ================

// =================================================================



// Student "类"

typedef struct {

    int id;

    char* name;

} Student;



// 辅助函数：创建 Student

Student* create_student(int id, const char* name) {

    Student* s = (Student*)malloc(sizeof(Student));

    if (!s) return NULL;

    s->id = id;

    s->name = strdup(name); // strdup 动态分配内存并复制字符串

    if (!s->name) {

        free(s);

        return NULL;

    }

    return s;

}



// 比较函数，利用 context 决定排序方式

int compare_student(const void* a, const void* b, void* context) {

    const Student* s_a = (const Student*)a;

    const Student* s_b = (const Student*)b;

    const char* sort_key = (const char*)context;



    // 根据 context（一个字符串）决定比较字段

    if (strcmp(sort_key, "name") == 0) {

        return strcmp(s_a->name, s_b->name);

    }



    // 默认或指定按 "id" 比较

    // if (strcmp(sort_key, "id") == 0)

    if (s_a->id < s_b->id) return -1;

    if (s_a->id > s_b->id) return 1;

    return 0;

}



// 释放 Student 数据

void free_student(void* data, void* context) {

    (void)context;

    Student* s = (Student*)data;

    free(s->name); // 先释放内部的字符串

    free(s);       // 再释放结构体本身

}



// 打印 Student 数据

void print_student(void* data, void* context) {

    (void)context;

    const Student* s = (const Student*)data;

    printf("(%d, %s) ", s->id, s->name);

}



void run_student_test() {

    printf("===== Running Student Test (using context) =====\n");



    // --- Part 1: 按 ID 排序 ---

    printf("\n--- Sorting by ID ---\n");

    const char* sort_by_id = "id";

    AVLTree* student_tree_by_id = avl_create(compare_student, free_student, (void*)sort_by_id);



    printf("Inserting students...\n");

    avl_insert(student_tree_by_id, create_student(5, "Charlie"));

    avl_insert(student_tree_by_id, create_student(2, "Alice"));

    avl_insert(student_tree_by_id, create_student(8, "Eve"));

    avl_insert(student_tree_by_id, create_student(1, "Bob"));

    avl_insert(student_tree_by_id, create_student(6, "David"));



    printf("Tree size: %zu\n", avl_size(student_tree_by_id));

    printf("Is tree valid? %s\n", avl_validate(student_tree_by_id) ? "Yes" : "No");

    printf("In-order traversal (should be by ID): ");

    avl_traverse_inorder(student_tree_by_id, print_student, NULL);

    printf("\n");



    printf("Destroying student tree (sorted by ID)...\n");

    avl_destroy(student_tree_by_id);

    print_line();



    // --- Part 2: 按 Name 排序 ---

    printf("\n--- Sorting by Name ---\n");

    const char* sort_by_name = "name";

    AVLTree* student_tree_by_name = avl_create(compare_student, free_student, (void*)sort_by_name);



    printf("Inserting same students...\n");

    avl_insert(student_tree_by_name, create_student(5, "Charlie"));

    avl_insert(student_tree_by_name, create_student(2, "Alice"));

    avl_insert(student_tree_by_name, create_student(8, "Eve"));

    avl_insert(student_tree_by_name, create_student(1, "Bob"));

    avl_insert(student_tree_by_name, create_student(6, "David"));



    printf("Tree size: %zu\n", avl_size(student_tree_by_name));

    printf("Is tree valid? %s\n", avl_validate(student_tree_by_name) ? "Yes" : "No");

    printf("In-order traversal (should be by Name): ");

    avl_traverse_inorder(student_tree_by_name, print_student, NULL);

    printf("\n");



    printf("Destroying student tree (sorted by Name)...\n");

    avl_destroy(student_tree_by_name);

    printf("Student test finished.\n");

}





// =================================================================

// ===================== 主函数入口 =================================

// =================================================================



int main() {

    run_integer_test();



    printf("\n\n================================================\n");

    printf("============== End of Integer Test =============\n");

    printf("================================================\n\n");



    run_student_test();



    return 0;

}