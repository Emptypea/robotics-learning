#include <stdio.h>

typedef struct{
    const char *label;
    const int *prices;
    size_t n;
    int expected;
}TestCase;

int max_profit(const int *prices, size_t n){
    int max = 0;
    size_t i = 0, j = i+1;
    while(j < n){
        int profit = prices[j] - prices[i];
        if(profit < 0){
            i = j;
        }
        else{
            if(profit > max){
                max = profit;
            }
        }
        j++;
    }
    return max;
}

int check(const char* label, int got, int expected){
    if(got != expected){
        printf("%s : FAIL, got %d, expected %d\n", label, got, expected);
        return 1;
    }
    printf("%s : PASS\n", label);
    return 0;
}


int main(void){
    TestCase tests[] = {
        {"Empty Array", NULL, 0, 0},
        {"Single Price", (int []){10}, 1, 0},
        {"Increasing Prices", (int []){1,2,3,4,5,6,7,8,9}, 9, 8},
        {"Decreasing Prices", (int []){9,8,7,6,5,4,3,2,1}, 9, 0},
        {"Irregular Pricing", (int []){10,5,8,11,17,2,14}, 7, 12},
        {"Same Price Throughout", (int []){3,3,3,3,3,3,3,3}, 8, 0},
        {"High, dip, rise, dip, rise, dip", (int []){7,2,5,3,6,4}, 6, 4}
    };
    
    size_t total = sizeof(tests)/sizeof(tests[0]);
    int errors = 0;

    for(size_t i = 0; i < total; i++){
        int got = max_profit(tests[i].prices, tests[i].n);
        errors += check(tests[i].label, got, tests[i].expected);
    }

    if(errors != 0){printf("%d TEST(S) FAILED!\n", errors);}
    else{printf("ALL TESTS PASSED\n");}

    return errors != 0;
}
