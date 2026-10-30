#include <stdio.h>
#include <stdlib.h>


typedef struct node{
	int val;
	struct node *next;
}Node;

Node *new_node(int v){
	Node *n = malloc(sizeof(Node));
	if(n==NULL){return NULL;}
	n->val = v;
	n->next = NULL;
	return n;
}

void push_front_pp(Node **headp, int v){
	Node *n = new_node(v);
	if(n==NULL){return;}
	n->next = *headp;
	*headp = n;
}

void remove_first(Node **headp){
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

int main(void){
	
    Node *head = NULL;

    remove_first(&head);
    print_list(head);

    push_front_pp(&head, 10);
    push_front_pp(&head, 20);
    push_front_pp(&head, 30);
    print_list(head);

    remove_first(&head);
    print_list(head);

    remove_first(&head);
    print_list(head);

    push_front_pp(&head, 40);
    print_list(head);

    free_all_pp(&head);
    print_list(head);

    printf("Head value after free all: %p\n", (void *)head);
	
	return 0;
}
