#include <stdio.h>
#include <stdlib.h>
#include "list_pp.h"


static Node *new_node(int v){
	Node *n = malloc(sizeof(Node));
	if(n==NULL){return NULL;}
	n->val = v;
	n->next = NULL;
	return n;
}

int push_front_pp(Node **headp, int v){
	Node *n = new_node(v);
	if(n==NULL){return -1;}
	n->next = *headp;
	*headp = n;
    return 0;
}

static void remove_first(Node **headp){
	if(*headp == NULL){return ;}
    Node *current = *headp;
	*headp = (*headp)->next;
	free(current);
}

void free_all_pp(Node **headp){
    while(*headp!=NULL){
        remove_first(headp);
    }
}

void print_list(const Node *head){
    for(const Node *p = head; p != NULL; p = p->next){
        printf("%d -> ", p->val);
    }
    printf("NULL\n");
}

size_t list_length(const Node *head){
    size_t count = 0;
    for(const Node *p = head; p != NULL; p = p->next){
        count++;
    }
    return count;
}
