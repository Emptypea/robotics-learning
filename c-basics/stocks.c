#include <stdio.h>

int max_profit(int arr[], int len){

    int profit = 0;
    for(int i=0; i<len-1; i++){
        for(int j=i+1; j<len; j++){
            int diff = arr[j] - arr[i];
            if(diff > profit){
                profit = diff;
            }
        }
    }

    return profit;
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
    
    int profit1 = max_profit(arr1, len1);
    int profit2 = max_profit(arr2, len2);
    int profit3 = max_profit(arr3, len3);
    int profit4 = max_profit(arr4, len4);

    printf("Maximum profit for arr1: %d\n", profit1);
    printf("Maximum profit for arr2: %d\n", profit2);
    printf("Maximum profit for arr3: %d\n", profit3);
    printf("Maximum profit for arr4: %d\n", profit4);

    return 0;
}