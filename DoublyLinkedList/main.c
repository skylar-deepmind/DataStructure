#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include "DoublyLinkedList.h"

int main(void) {

    DoublyLinkedList* list = list_create();
    list_append(list,(Song) { "As It Was", "Harry Styles", 167 });
    list_append(list,(Song) { "Levitating", "Dua Lipa", 203 });
    list_append(list,(Song) { "what's up", "4", 356 });
    list_append(list,(Song) { "Levitating2", "Dua Lipa", 203 });
    list_print_forward(list);
    Node* what = find_by_title(list,"what's up");
    if (what) {
        list_delete(list,what);list_print_forward(list);
    }
    Node* ins = find_by_title(list,"Levitating2");
    list_insert(list,ins,(Song) { "Industry Baby", "Lil Nas X", 212 });
    list_print_forward(list);
    return 0;
}