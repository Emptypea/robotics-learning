#include <stdio.h>

int max_profit_bruteforce(int arr[], int len){

    int max_profit = 0;
    for(int i=0; i<len-1; i++){
        for(int j=i+1; j<len; j++){
            int profit = arr[j] - arr[i];
            if(profit > max_profit){
                max_profit = profit;
            }
        }
    }

    return max_profit;
}

// The size of the array should be greater than 0
int max_profit_fast(int arr[], int len){

    int min_price = arr[0];
    int max_profit = 0;

    for(int i=1; i<len; i++){
        if(arr[i] < min_price){
            min_price = arr[i];
        } else {
            int profit = arr[i] - min_price;
            if(profit > max_profit){
                max_profit = profit;
            }
        }
    }
    return max_profit;
}


int main(void){
    int arr1[] = {7, 1, 5, 3, 6, 4};
    int len1 = sizeof(arr1)/sizeof(arr1[0]);

    int arr2[] = {7, 6, 4, 3, 1};
    int len2 = sizeof(arr2)/sizeof(arr2[0]);

    int arr3[] = {2, 10, 1};
    int len3 = sizeof(arr3)/sizeof(arr3[0]);

    int arr4[] = {5};
    int len4 = sizeof(arr4)/sizeof(arr4[0]);

    printf("Maximum profit for arr1 (bruteforce): %d\n", max_profit_bruteforce(arr1, len1));
    printf("Maximum profit for arr2 (bruteforce): %d\n", max_profit_bruteforce(arr2, len2));
    printf("Maximum profit for arr3 (bruteforce): %d\n", max_profit_bruteforce(arr3, len3));
    printf("Maximum profit for arr4 (bruteforce): %d\n", max_profit_bruteforce(arr4, len4));

    printf("Maximum profit for arr1 (fast): %d\n", max_profit_fast(arr1, len1));
    printf("Maximum profit for arr2 (fast): %d\n", max_profit_fast(arr2, len2));
    printf("Maximum profit for arr3 (fast): %d\n", max_profit_fast(arr3, len3));
    printf("Maximum profit for arr4 (fast): %d\n", max_profit_fast(arr4, len4));

    return 0;
}
