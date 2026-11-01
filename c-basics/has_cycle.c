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

void free_all_pp(Node **headp){
    while(*headp != NULL){
        Node *curr = *headp;
        *headp = (*headp)->next;
        free(curr);
    }
}

int has_cycle(Node *head){
    Node *slow = head, *fast = head;
    while(fast != NULL && fast->next != NULL){
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast){
            return 1; // Cycle detected
        }
    }
    return 0; // No cycle detected
}

int main(void){
    Node *head1 = NULL;

    int cycle_detected1 = has_cycle(head1);
    printf("Cycle detected in NULL: %s\n", cycle_detected1 ? "Yes" : "No");

    Node *head2 = new_node(1);
    int cycle_detected2 = has_cycle(head2);
    printf("Cycle detected in single node, 1 -> NULL: %s\n", cycle_detected2 ? "Yes" : "No");

    Node *head3 = new_node(1);
    head3->next = head3; // Creating a cycle
    int cycle_detected3 = has_cycle(head3);
    printf("Cycle detected in single node cycle, 1 -> 1: %s\n", cycle_detected3 ? "Yes" : "No");

    Node *a = new_node(1);
    Node *b = new_node(2);
    Node *c = new_node(3);
    Node *d = new_node(4);
    a->next = b;
    b->next = c;
    c->next = d;
    d->next = c; // Creating a cycle
    int cycle_detected4 = has_cycle(a);
    printf("Cycle detected in 1 -> 2 -> 3 -> 4 -> 3: %s\n", cycle_detected4 ? "Yes" : "No");

    Node *e = new_node(1);
    Node *f = new_node(2);
    Node *g = new_node(3);
    e->next = f;
    f->next = g;
    g->next = e; // Creating a cycle
    int cycle_detected5 = has_cycle(e);
    printf("Cycle detected in 1 -> 2 -> 3 -> 1: %s\n", cycle_detected5 ? "Yes" : "No");
    
    
    head3->next = NULL; // Break the cycle in list 3

    d->next = NULL; // Break the cycle in list 4

    g->next = NULL; // Break the cycle in list 5

    free_all_pp(&head1);
    free_all_pp(&head2);
    free_all_pp(&head3);
    free_all_pp(&a);
    free_all_pp(&e);

    return 0;
}
