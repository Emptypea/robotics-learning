#include <stdio.h>

int main(void) {
    int arr[5] = {10, 20, 30, 40, 50};
    int *p = arr;
    int *end = arr + 5;

    p++;
    printf("L1: %d\n", *p);

    p += 2;
    printf("L2: %d\n", *p);

    printf("L3: %td\n", p - arr);
    printf("L4: %td\n", end - p);

    printf("L5: %d\n", p < end);

    int v = *p++;
    printf("L6: %d %d\n", v, *p);

    (*p)++;
    printf("L7: %d %d\n", *p, arr[4]);

    p++;
    printf("L8: %d\n", p == end);

    return 0;
}
