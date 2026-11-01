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

void free_all_pp(Node **headp){
    while(*headp != NULL){
        Node *curr = *headp;
        *headp = (*headp)->next;
        free(curr);
    }
}

Node *middle_of_list(Node *head){
    Node *slow = head, *fast = head;
    while(fast != NULL && fast->next != NULL){
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

void print_middle(Node *mid){
    if(mid != NULL){
        printf("Middle element: %d\n", mid->val);
    } else {
        printf("List is empty, no middle element.\n");
    }
}

void print_list(Node *head){
    for(Node *p = head; p != NULL; p = p->next){
        printf("%d ->", p->val);
    }
    printf("NULL\n");
}

int main(void){
    Node *head = NULL;
    Node *mid_1 = middle_of_list(head);
    print_list(head);
    print_middle(mid_1);

    push_front_pp(&head, 6);
    Node *mid_2 = middle_of_list(head);
    print_list(head);
    print_middle(mid_2);

    push_front_pp(&head, 5);
    Node *mid_3 = middle_of_list(head);
    print_list(head);
    print_middle(mid_3);
    
    push_front_pp(&head, 4);
    push_front_pp(&head, 3);
    push_front_pp(&head, 2);
    Node *mid_4 = middle_of_list(head);
    print_list(head);
    print_middle(mid_4);
    
    push_front_pp(&head, 1);
    Node *mid_5 = middle_of_list(head);
    print_list(head);
    print_middle(mid_5);

    free_all_pp(&head);
    return 0;
}
