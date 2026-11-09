#include <stdio.h>

int single_number(const int *a, size_t n){
    int num = 0;
    for(size_t i = 0; i < n; i++){
        num ^= a[i];
    }
    return num;
}

static int check(const char *label, int got, int expected){
    if(got != expected){
        printf("FAILED %s: got %d, expected %d\n", label, got, expected);
        return 1;
    }
    printf("PASSED %s\n", label);
    return 0;
}

int main(void){
    int a1[] = {1};
    size_t len1 = sizeof(a1)/sizeof(a1[0]);
    int a2[] = {2,3,4,5,5,4,3};
    size_t len2 = sizeof(a2)/sizeof(a2[0]);
    int a3[] = {3,4,5,5,4,3,10};
    size_t len3 = sizeof(a3)/sizeof(a3[0]);
    int a4[] = {3,4,5,7,5,4,3};
    size_t len4 = sizeof(a4)/sizeof(a4[0]);
    int a5[] = {3,4,5,-1,5,4,3};
    size_t len5 = sizeof(a5)/sizeof(a5[0]);
    int a6[] = {-3,-4,5,-1,-1,-4,-3};
    size_t len6 = sizeof(a6)/sizeof(a6[0]);

    int err = 0;

    err += check("One element", single_number(a1, len1), 1);
    err += check("Single value first", single_number(a2, len2), 2);
    err += check("Single value last", single_number(a3, len3), 10);
    err += check("Single value in the middle", single_number(a4, len4), 7);
    err += check("Negative single value", single_number(a5, len5), -1);
    err += check("Negative values in the pairs", single_number(a6, len6), 5);

    if(err == 0){
        printf("PASSED on all test cases\n");
    } else {
        printf("FAILED\n");
    }
    return err != 0;
}
