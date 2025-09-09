

// main.c



#include "safeArray.h"

#include <stdio.h>



void plain_c_array_example() {

    printf("--- 1. 普通C数组的危险性 ---\n");

    int normal_array[5] = { 10, 20, 30, 40, 50 };



    printf("尝试读取越界索引 10...\n");

    // 这行代码在编译时可能不会报错，但运行时会读取到未知的内存垃圾值，

    // 或者直接导致程序崩溃。这就是“不安全”。

    int garbage = normal_array[10];

    printf("读取到的垃圾值: %d (这是未定义行为!)\n", garbage);



	// update the value at index 2

	normal_array[2] = 99; // 正常写入







    // MyIntArr* myarr = normal_array_create(5);



	// bool res = update_arr(myarr, 2, 99);

    // 封装

    printf("尝试写入越界索引 -5...\n");

    // 这比读取更危险，它会污染程序其他部分的内存，导致难以追踪的bug。

    // normal_array[-5] = 999; // (取消注释这行可能会导致程序崩溃)

    printf("写入操作可能已破坏了内存！\n\n");





	printf("普通C数组的使用是危险的，因为它没有任何安全检查。\n");





}



void safe_array_example() {

    printf("--- 2. 使用我们的“安全数组” ---\n");



	// SafeArray my_array = { .data = NULL, .capacity = 0 };



    // API 函数原型

    // C语言函数库 C原型





    // 创建一个容量为5的安全数组

    SafeArray* sa = sarray_create(5);

    if (!sa) {

        printf("创建安全数组失败。\n");

        return;

    }

    printf("安全数组创建成功。\n");

    sarray_print(sa); // 初始应为0（或随机值，取决于系统）









    // 安全地设置值

    printf("\n安全地设置值...\n");

    for (size_t i = 0; i < sarray_get_capacity(sa); i++) {

        sarray_set(sa, i, (i + 1) * 11);

    }

    sarray_print(sa);



    // 尝试安全地写入越界索引

    printf("\n尝试安全地写入越界索引 10...\n");

    if (sarray_set(sa, 10, 999)) {

        printf("写入成功 (不应发生!)\n");

    }

    else {

        printf("写入失败，因为索引越界。程序安全！\n");

    }

    sarray_print(sa); // 数组内容没有被破坏



    // 安全地获取值

    printf("\n安全地获取值...\n");

    int value;

    if (sarray_get(sa, 3, &value)) {

        printf("索引 3 的值为: %d\n", value);

    }



    // 尝试安全地读取越界索引

    printf("\n尝试安全地读取越界索引 5...\n");



    // SafeArray* sa = sarray_get(xxx);



    // sa->data = "123";





    if (sarray_get(sa, 5, &value)) {

        printf("读取到的值: %d (不应发生!)\n", value);

    }

    else {

        printf("读取失败，因为索引越界。程序安全！\n");

    }



    sarray_destroy(&sa);

    printf("\n安全数组已销毁。\n");

}



int main() {

    plain_c_array_example();

    safe_array_example();



    return 0;

}