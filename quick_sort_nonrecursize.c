#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(int argc, char **argv) {
    size_t count = 20;
    srand(time(0));
    node_t *list = NULL;
    while (count--) {
        list = list_make_node_t(list, rand() % 1024);
    }
    
    list_display(list);
    quicksort_nonrecursive(&list, 20);
    list_display(list);

    if (!list_is_ordered(list))
        return EXIT_FAILURE;
    list_free(list);
    return EXIT_SUCCESS;
}        