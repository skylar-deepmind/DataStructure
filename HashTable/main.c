// main.c



#include "hashTable.h"

#include <stdio.h>



int main() {

    printf("--- 现代哈希表 C语言实现 (拉链法) ---\n");

    HashTable* ht = ht_create(10); // 创建容量为10的哈希表

    if (!ht) {

        printf("创建哈希表失败。\n");

        return 1;

    }



    printf("\n1. 插入初始数据 (包括哈希冲突)...\n");

    // hash("name") % 10 = (110+97+109+101)%10 = 417%10 = 7 (注：ASCII码不同机器可能微调，但冲突原理一致)

    // hash("mane") % 10 = (109+97+110+101)%10 = 417%10 = 7

    ht_set(ht, "name", "Alice");

    ht_set(ht, "age", "30");

    ht_set(ht, "city", "New York");

    ht_set(ht, "mane", "Bob"); // <-- 这个键会与 "name" 发生哈希冲突

    ht_print(ht);



    printf("2. 查找数据...\n");

    const char* name = ht_get(ht, "name");

    const char* city = ht_get(ht, "city");

    const char* country = ht_get(ht, "country"); // 一个不存在的键

    printf("Get 'name': %s\n", name ? name : "Not Found");

    printf("Get 'city': %s\n", city ? city : "Not Found");

    printf("Get 'country': %s\n", country ? country : "Not Found");



    // 查找冲突链中的另一个键

    const char* mane = ht_get(ht, "mane");

    printf("Get 'mane' (collision key): %s\n", mane ? mane : "Not Found");

    printf("\n");



    printf("3. 更新数据...\n");

    printf("Updating 'name' from 'Alice' to 'Amy'...\n");

    ht_set(ht, "name", "Amy");

    ht_print(ht);



    printf("4. 删除数据...\n");

    printf("Removing 'age'...\n");

    ht_remove(ht, "age");

    ht_print(ht);



    printf("Removing 'name' (a key in a collision chain)...\n");

    ht_remove(ht, "name");

    ht_print(ht);



    printf("5. 销毁哈希表...\n");

    ht_destroy(&ht);

    printf("哈希表已销毁，指针为: %s\n", ht == NULL ? "NULL" : "OK");



    return 0;

}