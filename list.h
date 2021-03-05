#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <time.h>

#define  MAX_LEVELS  1000

typedef struct __node {                   
    int value;
    struct __node *next;
} node_t;

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

static inline node_t *find_ele(node_t *head, int pos){
    node_t *ptr = head;
    for(int i = 0; i < pos; i++){
        ptr = ptr->next;
    }
    return ptr;
}

static inline int find_ele_byVal(node_t *head, int target){
    node_t *ptr = head;
    int pos = 0;
    while (ptr->value != target) {
        pos ++;
        ptr = ptr->next;
    }
    return pos;
}

static inline void move_node(node_t **list, int pos, int des){
    if(pos == des){
        return;
    }
    node_t *ptr = *list;
    for(int i = 0; i < pos; i++){
        ptr = ptr->next;
    }
    node_t *temp = ptr;
    if (ptr == *list) {
        *list = (*list)->next;
    } else {
        ptr = *list;
        for(int i = 0; i < pos - 1; i++){
            ptr = ptr->next;
        }
        ptr->next = temp->next;
        temp->next = NULL;
    }
    // if(pos < des){
    //     des--;
    // }
    // if(des != 0 && find_ele(*list, des)->value < temp->value){
    //     des ++;
    // }
    if (des == 0) {
        temp->next = *list;
        *list = temp;
    } else {
        ptr = *list;
        for(int i = 0; i < des - 1; i++){
            ptr = ptr->next;
        }
        temp->next = ptr->next;
        ptr->next = temp;
    }
}

static void list_show(node_t *list) {
    while (list) {
        printf("%d ", list->value);
        list = list->next;
    }
    printf("\n");
}

void quicksort_nonrecursive(node_t **list, int size)
{
    if (!*list)
        return;

    int beg[MAX_LEVELS], end[MAX_LEVELS], i=0, L, R, piv_pos;
    node_t *piv, *temp;
    beg[0] = 0; 
    end[0] = size;
    while (i >= 0) {
        L = beg[i]; 
        R = end[i]-1;
        if (L <  R) {
            piv = find_ele(*list, L); 
            if (i == MAX_LEVELS-1) 
                return;
            while (L < R) {
                while (find_ele(*list, R)->value >= piv->value && L < R) {
                    R--;
                }   
                if (L < R) {
                    move_node(list, R, L);
                    L++;
                }
                while (find_ele(*list, L)->value <= piv->value && L < R) {
                    L++;
                }
                if (L < R) {
                    move_node(list, L, R); 
                    R--;
                }
            }
                if (find_ele(*list, L)->value > piv->value) {
                    R--;
                    L--;
                }
            move_node(list, find_ele_byVal(*list, piv->value), L);
            beg[i + 1] = L + 1; 
            end[i + 1] = end[i]; 
            end[i++] = L; 
        } else {
            i--; 
        }
    }
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