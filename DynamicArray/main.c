#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DynamicArray.h"

int main(void) {
    DynamicArray* arr =  create_array(10);
    print_array(arr);
    append_array(arr,1);
    append_array(arr,2);
    append_array(arr,3);
    append_array(arr,4);
    append_array(arr,5);
    print_array(arr);
    append_array(arr,6);
    append_array(arr,7);
    append_array(arr,8);
    print_array(arr);
    delete_array(arr,0);
    print_array(arr);
    insert_array(arr,0,1);
    print_array(arr);
    update_array(arr,5,10);
    print_array(arr);
    destroy_array(arr);

    return 0;
}
