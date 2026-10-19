#include <stdio.h>

int main(void){
    int arr[3] = {10,20,30};

    printf("%p %p %p\n", (void *)&arr[0], (void *)&arr[1], (void *)&arr[2]);
    printf("%p\n", (void *)arr); 
    printf("%p\n", (void *)(arr + 2));  
    printf("%d %d\n", *(arr + 1), arr[2]); 
    printf("%zu %zu\n", sizeof arr, sizeof arr[0]);

    printf("%d %d\n", *arr + 1, *(arr + 1));

    return 0;
}