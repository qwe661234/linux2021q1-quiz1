#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <time.h>
#include <spral_random.h>
#include "list.h"

static inline void list_add_node_t(node_t **list, node_t *node_t) {
    node_t->next = *list;
    *list = node_t;
}

static inline void list_concat(node_t **left, node_t *right) {
    while (*left)
        left = &((*left)->next);
    *left = right;
}

void quicksort(node_t **list)
{
    if (!*list)
        return;

    node_t *pivot = *list;
    int value = pivot->value;
    node_t *p = pivot->next;
    pivot->next = NULL;

    node_t *left = NULL, *right = NULL;
    while (p) {
        node_t *n = p;
        p = p->next;
        list_add_node_t(n->value > value ? &right : &left, n);
    }

    quicksort(&left);
    quicksort(&right);

    node_t *result = NULL;
    list_concat(&result, left);
    list_concat(&result, pivot); 
    list_concat(&result, right);
    *list = result;
}

static bool list_is_ordered(node_t *list) {
    bool first = true;
    int value;
    while (list) {
        if (first) {
            value = list->value;
            first = false;
        } else {
            if (list->value < value)
                return false;
            value = list->value;
        }
        list = list->next;
    }
    return true;
}

static void list_display(node_t *list) {
    printf("%s IN ORDER : ", list_is_ordered(list) ? "   " : "NOT");
    while (list) {
        printf("%d ", list->value);
        list = list->next;
    }
    printf("\n");
}

static void list_free(node_t *list){
    node_t *ptr;
    while (list) {
        ptr = list;
        list = list->next;
        free(ptr);
    }
}

static node_t* list_make_node_t(node_t *list, int value){
    node_t *newh = malloc(sizeof(node_t));
    newh->value = value;
    if (list == NULL) {
        newh->next = NULL;
    } else {
        newh->next = list;
    }
    return newh;
}
int main(int argc, char **argv) {
    size_t count = 20;
    srand(time(0));
    node_t *list = NULL;
    while (count--) {
        list = list_make_node_t(list, rand() % 1024);
    }
        

    list_display(list);
    quicksort(&list);
    list_display(list);

    if (!list_is_ordered(list))
        return EXIT_FAILURE;
    list_free(list);
    return EXIT_SUCCESS;
}        