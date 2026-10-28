#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int value;
    struct node *next;
} Node;

Node *new_node(int x){
    Node *n = malloc(sizeof(Node));
    if(n == NULL){return NULL;}
    n->value = x;
    n->next = NULL;
    return n;
}

Node *push_front(Node *head, int x){
    Node *n = new_node(x);
    if(n == NULL){return head;}
    n->next = head;
    return n;
}

void print_list(const Node *head){
    for(const Node *p = head; p != NULL; p = p->next){
        printf("%d -> ", p->value);
    }
    printf("NULL\n");
}

void free_list(Node *head){
    Node *old = head;
    while(head != NULL){
        head = head->next;
        free(old);
        old = head;
    }
}

size_t list_length(const Node *head){
    size_t count = 0;
    for(const Node *p = head; p != NULL; p = p->next){
        count++;
    }
    return count;
}

int main(void){
    Node *head = NULL;
    print_list(head);
    printf("Length: %zu\n", list_length(head));
    head = push_front(head, 30);
    print_list(head);
    printf("Length: %zu\n", list_length(head));
    head = push_front(head, 20);
    print_list(head);
    printf("Length: %zu\n", list_length(head));
    head = push_front(head, 10);
    print_list(head);
    printf("Length: %zu\n", list_length(head));

    free_list(head);
    head = NULL;

    return 0;
}
