#include <stdio.h>
#include <stddef.h>

typedef struct testcase{
    const char *label;
    int *a;
    size_t n;
    int expected_res;
    size_t expected_out;
}TestCase;

int pivot_index(const int *a, size_t n, size_t *out){
    if(a == NULL || out == NULL || n ==0){return -1;}
    
    int lsum = 0, rsum = 0;
    for(size_t i = 0; i < n; i++){
        rsum += a[i];
    }

    for(size_t j = 0; j < n; j++){
        rsum = rsum - a[j];
        if(lsum == rsum){
            *out = j;
            return 0;
        }
        lsum += a[j];
    }

    return -1;
}

int check(const char* label, const char *attribute, int got, int expected){
    if(got != expected){
        printf("%s - %s : FAIL, got %d, expected %d\n", label, attribute, got, expected);
        return 1;
    }
    printf("%s - %s : PASS\n", label, attribute);
    return 0;
}

int main(void){
    TestCase tests[] = {
        { "example1",       (int[]){1, 7, 3, 6, 5, 6},  6,  0,  3 },
        { "no pivot",       (int[]){1, 2, 3},           3, -1, 99 },
        { "pivot at 0",     (int[]){2, 1, -1},          3,  0,  0 },
        { "empty",          (int[]){0},                 0, -1, 99 },
        { "one element",    (int[]){5},                 1,  0,  0 },
        { "two pivots",     (int[]){2, 0, 0, 2},        4,  0,  1 },
        { "last index",     (int[]){1, -1, 5},          3,  0,  2 },
        { "all negatives",  (int[]){-1, -1, -1},        3,  0,  1 },

    };

    int fail = 0;
    int res = 0;
    size_t len_tests = sizeof(tests)/sizeof(tests[0]);

    for(size_t i = 0; i < len_tests; i++){
        size_t out = 99;
        res = pivot_index(tests[i].a, tests[i].n, &out);
        fail += check(tests[i].label, "checking return", res, tests[i].expected_res);
        fail += check(tests[i].label, "checking out value", (int)out, (int)tests[i].expected_out);
    }
    printf("%d checks FAILED\n", fail);
    return fail != 0;
}
