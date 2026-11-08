#include <stdio.h>
#include "list_pp.h"

/* returns 1 on fail, 0 on pass */
static int check(const char *label, long got, long expected)
{
    if (got != expected) {
        printf("FAIL %s: got %ld, expected %ld\n", label, got, expected);
        return 1;
    }
    printf("ok   %s\n", label);
    return 0;
}

int main(void)
{
    int fails = 0;
    Node *head = NULL;

    /* empty list */
    fails += check("empty: length", (long)list_length(head), 0);

    /* push 10 */
    fails += check("push 10: return", push_front_pp(&head, 10), 0);
    fails += check("push 10: length", (long)list_length(head), 1);
    if (head != NULL) {
        fails += check("push 10: head value", head->val, 10);
    }

    /* push 20 and 30 */
    fails += check("push 20: return", push_front_pp(&head, 20), 0);
    fails += check("push 30: return", push_front_pp(&head, 30), 0);
    fails += check("3 pushes: length", (long)list_length(head), 3);
    if (head != NULL) {
        fails += check("3 pushes: head value", head->val, 30);
    }

    /* free */
    free_all_pp(&head);
    fails += check("free: head is NULL", head == NULL, 1);

    return fails != 0;
}
