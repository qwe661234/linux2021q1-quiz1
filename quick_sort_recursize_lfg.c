#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(int argc, char **argv) {
    
    int f[100], op, j, k, out;
    f[0] = 1;
    f[1] = 1;
    for(int i = 2; i < 100; i++){
        f[i] = f[i - 1] + f[i - 2];
    }

    size_t count = 20;
    srandom(time(0));
    node_t *list = NULL;
    while (count--) {
        op = random() % 4;
        j = random() % 100;
        k = random() % 100;
        switch(op){
            case 0:
                out = f[99 - j] + f[99 -k];
                break;
            case 1:
                out = f[99 - j] - f[99 -k];
                break;
            case 2:
                out = f[99 - j] * f[99 -k];
                break;
            case 3:
                out = f[99 - j]^f[99 -k];
                break;
        }
        list = list_make_node_t(list, out % 1024);
    }
        

    list_display(list);
    quicksort(&list);
    list_display(list);

    if (!list_is_ordered(list))
        return EXIT_FAILURE;
    list_free(list);
    return EXIT_SUCCESS;
}        