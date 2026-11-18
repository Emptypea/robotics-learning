#include <stdio.h>

typedef struct testcases{
    const char *label;
    size_t n;
    int *input;
    const int *expected;
}Testcases;

void move_zeroes(int *a, size_t n){
    size_t i = 0, j = i+1;
    while(j < n){
        if(a[i] == 0){
            if(a[j] != 0){
                int temp = a[i];
                a[i] = a[j];
                a[j] = temp; 
                i++;
            }
        }
        else{i++;}
        j++;
    }
}

int check(const char *label, const int *got, const int *expected, size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (got[i] != expected[i]) {
            printf("%s : FAIL. got %d, expected %d at index %zu\n", label, got[i], expected[i], i);
            return 1;
        }
    }
    printf("%s : PASS\n", label);
    return 0;
}

int main(void){
    Testcases tests[] = {
        {"Empty" ,                  0,      NULL,                                   NULL},
        {"One Element",             1,      (int[]){0},                             (const int[]){0} },
        {"Zeroes First",            6,      (int[]){0,0,0,5,8,9},                   (const int[]){5,8,9,0,0,0} },
        {"Alternating",             9,      (int[]){1,0,2,0,3,0,4,0,5},             (const int[]){1,2,3,4,5,0,0,0,0} },
        {"Zeros in the middle",     9,      (int[]){4,5,6,0,0,0,7,8,9},             (const int[]){4,5,6,7,8,9,0,0,0} },
        {"Zeroes Last",             11,     (int[]){10,11,12,13,14,0,0,0,0,0,0},    (const int[]){10,11,12,13,14,0,0,0,0,0,0} },
        {"All Zeroes",              7,      (int[]){0,0,0,0,0,0,0},                 (const int[]){0,0,0,0,0,0,0} },
        {"No Zeroes",               6,      (int[]){5,10,15,20,25,30},              (const int[]){5,10,15,20,25,30} }
    };

    size_t n = sizeof(tests) / sizeof(tests[0]);
    int fails = 0;

    int a[1] = {7};
    move_zeroes(a, 0);
    fails += check("Empty: a[0] untouched", a, (const int[]){7}, 1);

    for(size_t i = 0; i < n; i++){
        move_zeroes(tests[i].input, tests[i].n);
        fails += check(tests[i].label, tests[i].input, tests[i].expected, tests[i].n);
    }

    return fails != 0;
}
