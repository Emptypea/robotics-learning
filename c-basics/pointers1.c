#include <stdio.h>

int main(void){
    int x = 10;
    int *p = &x;
    printf("%d\n", x);
    printf("%d\n", *p);
    *p = 25;
    printf("%d\n", x);
    x = 40;
    printf("%d\n", *p);
    printf("%zu %zu\n", sizeof(x), sizeof(p));

    printf("%p\n", (void *)&x);
    printf("%p\n", (void *)p);
    printf("%p\n", (void *)&p);

    return 0;
}
