#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int val;
    struct node *next;
}Node;

Node *new_node(int v){
    Node *n = malloc(sizeof(Node));
    if(n == NULL){return NULL;}
    n->val = v;
    n->next = NULL;

    return n;
}

void push_front_pp(Node **headp, int v){
    Node *n = new_node(v);
    if(n == NULL){return ;}

    n->next = *headp;
    *headp = n;
}

void remove_first_pp(Node **headp){
    if(*headp == NULL){return;}
    Node *curr = *headp;
    *headp = (*headp)->next;
    free(curr);
}

void free_all_pp(Node **headp){
    while(*headp != NULL){
        remove_first_pp(headp);
    }
}

void print_list(Node *head){
    for(Node *p = head; p != NULL; p = p->next){
        printf("%d ->", p->val);
    }
    printf("NULL\n");
}

size_t list_length(Node *head){
    size_t count = 0;
    Node *p = head;
    while(p != NULL){
        count++;
        p = p->next;
    }

    return count;
}


void reverse_list_pp(Node **headp){
    Node *prev = NULL, *curr = *headp, *next = NULL;
    while(curr != NULL){
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    *headp = prev;
}


int main(void){

    Node *head = NULL;
    print_list(head);
    reverse_list_pp(&head);
    print_list(head);

    push_front_pp(&head, 10);
    print_list(head);
    reverse_list_pp(&head);
    print_list(head);

    push_front_pp(&head, 20);
    push_front_pp(&head, 30);
    print_list(head);
    reverse_list_pp(&head);
    print_list(head);

    free_all_pp(&head);

    return 0;
}
