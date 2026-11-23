#include <stdio.h>
#include <stdlib.h>

typedef struct testcase{
    const char *label;
    int *input;
    size_t n;
    int *expected;
}TESTCASE;

int *sorted_squares(const int *a, size_t n, int *out){
    if(n == 0){return out;}

    size_t left = 0, right = n, write = n;
    while(write > 0){
        int sq_l = a[left] * a[left], sq_r = a[right-1] * a[right-1];
        if(sq_l > sq_r){
            out[write-1] = sq_l;
            left++;
        }
        else{
            out[write-1] = sq_r;
            right--;
        }
        write--;
    }
    return out;
}

int *create_arr_with_sentinel(size_t n, int val){

    int *arr = malloc((n+1) * sizeof(*arr));
    if(arr == NULL){return NULL;}

    for(size_t i = 0; i <= n; i++){
        arr[i] = val;
    }
    return arr;

}

void check_equals(const char *label, const int *got,const int *expected, size_t n, int *failed_checks, int *total_checks, int row_failed){
    int mismatches = 0;
    for(size_t i = 0; i < n; i++){
        (*total_checks)++;
        if(got[i] != expected[i]){
            printf("%s : FAIL, got[%zu] is %d, expected[%zu] is %d\n",
                    label, i, got[i], i, expected[i]);
            (*failed_checks)++;
            mismatches++;
        }
    }
    if(!row_failed && mismatches == 0){
        printf("%s : PASS\n", label);
    }

}

int main(void){
    TESTCASE tests[] = {
        {"empty",               (int[]){0},                0,      (int[]){0}                     },
        {"one negative",        (int[]){-5},               1,      (int[]){25}                    },
        {"one zero",            (int[]){0},                1,      (int[]){0}                     },
        {"all negative",        (int[]){-7, -3, -2},       3,      (int[]){4,9,49}                },
        {"all non-negative",    (int[]){0, 2, 5},          3,      (int[]){0, 4, 25}              },
        {"mixed with zero",     (int[]){-4, -1, 0, 3, 10}, 5,      (int[]){0, 1, 9, 16, 100}      },
        {"equal magnitude",     (int[]){-3, -1, 1, 3},     4,      (int[]){1, 1, 9, 9}            },
        {"max magnitude",       (int[]){-10000, 10000},    2,      (int[]){100000000, 100000000}  }
    };

    int failed_checks = 0;
    int total_checks = 0;
    size_t len_tests = sizeof(tests)/sizeof(tests[0]);

    for(size_t i = 0; i < len_tests; i++){
        int *got = create_arr_with_sentinel(tests[i].n, 99);
        if(got == NULL){
            fprintf(stderr, "%s : FAIL (allocation failed)\n", tests[i].label);
            failed_checks++;
            total_checks++;
            continue;
        }

        int *ret = sorted_squares(tests[i].input, tests[i].n, got);

        int row_failed = 0;

        total_checks++;
        if(got[tests[i].n] != 99){
            printf("%s : FAIL, sentinel at index %zu was overwritten\n", tests[i].label, tests[i].n);
            failed_checks++;
            row_failed = 1;
        }


        total_checks++;
        if(ret != got){
            printf("%s : FAIL, return value did not match out pointer\n", tests[i].label);
            failed_checks++;
            free(got);
            continue;
        }

        check_equals(tests[i].label, got, tests[i].expected, tests[i].n,
                    &failed_checks, &total_checks, row_failed);
        free(got);
    }

    printf("%d of %d checks FAILED\n", failed_checks, total_checks);
    return failed_checks != 0;
}
