#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define MODE_SHIFT 4
#define MODE_MASK (0x7u << MODE_SHIFT)

typedef struct Node{
    int value;
    struct Node *next;
}Node;

uint32_t bit_set(uint32_t x, unsigned n){
    return x | (1u << n);
}

uint32_t bit_clear(uint32_t x, unsigned n){
    return x& ~(1u << n);
}

uint32_t bit_toggle(uint32_t x, unsigned n){
    return x ^ (1u << n);
}

int bit_test(uint32_t x, unsigned n){
    return (x >> n) & 1u;
}

uint32_t mode_read(uint32_t reg){
    return (reg & MODE_MASK) >> MODE_SHIFT;
}

uint32_t mode_write(uint32_t reg, uint32_t value){
    return (reg & ~MODE_MASK) | ((value << MODE_SHIFT) & MODE_MASK);
}

int check(const char* label, uint32_t got, uint32_t expected){
    if(got != expected){
        printf("%-28s\tFAIL: got 0x%08x, expected 0x%08x\n", label, got, expected);
        return 1;
    }
    printf("%-28s\tPASS\n", label);
    return 0;
}

static Node *new_node(int x){
    Node *new_node = malloc(sizeof(Node));
    if(new_node == NULL){
        return NULL;
    }
    new_node->value = x;
    new_node->next = NULL;

    return new_node;
}

int push_front(Node **headp, int val){
    Node *node = new_node(val);
    if(node == NULL){
        return -1;
    }
    node->next = *headp;
    *headp = node;

    return 0;
}

int pop_front(Node **headp, int *out){
    if(*headp == NULL) {
        return -1;
    }
    Node *curr_node = *headp;
    *headp = (*headp)->next;
    *out = curr_node->value; 
    free(curr_node);

    return 0;
}

size_t length(const Node *head){
    size_t count = 0;
    if(head == NULL){
        return count;
    }
    for(const Node *p = head; p != NULL; p = p->next){
        count++;
    }
    return count;
}

void free_all(Node **headp){
    if (*headp == NULL){
        return;
    }
    Node *curr_node = *headp;
    while(*headp != NULL){
        *headp = (*headp)->next;
        free(curr_node);
        curr_node = *headp; 
    }
}


int check_push_pop(const char *label, int got, int expected){
    if(got != expected){
        printf("%s FAIL: Got %d, expected %d\n", label, got, expected);
        return 1;
    }
    printf("%s PASS\n", label);
    return 0;
}



int main(void){
    int err = 0;

    err += check("set: all 0s, bit 1", bit_set(0x00000000, 1), 0x00000002);
    err += check("set: bit 31 already 1", bit_set(0xFFFFFFFF, 31), 0xFFFFFFFF);
    err += check("set: middle bit 16", bit_set(0x00000001, 16), 0x00010001);
    err += check("clear: all 1s, bit 12", bit_clear(0xFFFFFFFF, 12), 0xFFFFEFFF);
    err += check("clear: bit already 0", bit_clear(0x0000000A, 2), 0x0000000A);
    err += check("clear: bit 0", bit_clear(0xF0F0F0FF, 0), 0xF0F0F0FE);
    err += check("toggle 0 to 1", bit_toggle(0x00000008, 2), 0x0000000C);
    err += check("toggle:twice restore", bit_toggle(bit_toggle(0x0000000A, 2), 2), 0x0000000A);
    err += check("toggle:bit 31, 1 to 0", bit_toggle(0xF0000000, 31), 0x70000000);
    err += check("test: bit is 0", bit_test(0xDFFFFFFF, 29), 0);
    err += check("test: bit is 1", bit_test(0x00000A00, 11), 1);

    uint32_t reg = 0x0000ABCD;
    err += check("read: mixed value", mode_read(reg), 0x00000004);
    
    reg = 0xFFFFFFFF;
    err += check("read: max value", mode_read(reg), 0x00000007);

    reg = mode_write(reg, 0x00000008);
    err += check("write: too large, all 1s", reg, 0xFFFFFF8F);

    reg = 0x00000000;
    reg = mode_write(reg, 0x00000007);
    err += check("write: max value, all 0s", reg, 0x00000070);

    if(err == 0){
        printf("All bit and field test cases PASSED\n");
    }
    else{
        printf("FAILED: bit and field test cases\n");
    }

    Node *head = NULL;
    int push = 0;
    int out = 0;
    int pop = 0;
    size_t len = 0;


    len = length(head);
    err += check_push_pop("Empty Linked List Length", len, 0);

    pop = pop_front(&head, &out);
    err += check_push_pop("Pop Front: Empty List", pop, -1);
    err += check_push_pop("Out Value: Initial pop", out, 0);

    push = push_front(&head, 40);
    err += check_push_pop("Push Front: 40", push, 0);
    push = push_front(&head, 30);
    err += check_push_pop("Push Front: 30", push, 0);
    push = push_front(&head, 20);
    err += check_push_pop("Push Front: 20", push, 0);

    len = length(head);
    err += check_push_pop("Linked List Length", len, 3);

    pop = pop_front(&head, &out);
    err += check_push_pop("Pop Front: 20", pop, 0);
    err += check_push_pop("Out Value = 20", out, 20);

    len = length(head);
    err += check_push_pop("Length after Pop", len, 2);
    
    pop = pop_front(&head, &out);
    err += check_push_pop("Pop Front: 30", pop, 0);
    err += check_push_pop("Out Value = 30", out, 30);
    
    pop = pop_front(&head, &out);
    err += check_push_pop("Pop Front: 40", pop, 0);
    err += check_push_pop("Out Value = 40", out, 40);

    pop = pop_front(&head, &out);
    err += check_push_pop("Pop Front: After popping last element", pop, -1);
    err += check_push_pop("Out Value = 40", out, 40);

    free_all(&head);
    if(head != NULL){
        printf("Free FAILED\n");
        err += 1;
    }

    push = push_front(&head, 30);
    err += check_push_pop("Push Front: 30", push, 0);
    push += push_front(&head, 20);
    err += check_push_pop("Push Front: 20", push, 0);
    push += push_front(&head, 10);
    err += check_push_pop("Push Front: 10", push, 0);

    free_all(&head);
    if(head != NULL){
        printf("Free FAILED\n");
        err += 1;
    }

    return err != 0;

}
