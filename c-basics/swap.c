#include <stdio.h>

void swap_val(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
}

void swap_ptr(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main(void) {
    int x = 1, y = 2;
    swap_val(x, y);
    printf("after swap_val: x = %d, y = %d\n", x, y);
    swap_ptr(&x, &y);
    printf("after swap_ptr: x = %d, y = %d\n", x, y);
    return 0;
}
