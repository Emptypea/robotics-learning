#ifndef LIST_PP_H
#define LIST_PP_H

#include <stddef.h>

typedef struct node{
    int val;
    struct node *next;
} Node;

int push_front_pp(Node **headp, int v);
void free_all_pp(Node **headp);
void print_list(const Node *head);
size_t list_length(const Node *head);

#endif /* LIST_PP_H */
