#include <stdio.h>

void reverse(int *arr, size_t n){

    int *forward = arr;
    int *backward = arr + n;
    while (forward < backward) {
        int temp = *forward;
        *forward = *--backward;
        *backward = temp;
        forward++;
    }
}

void print_array(const int *arr, size_t n){
    for(size_t i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void){
    int arr1[] = {9,8};
    size_t n1 = sizeof(arr1) / sizeof(arr1[0]);
    reverse(arr1, 0);
    printf("Reverse array with n='%zu' is: ",(size_t)0);
    print_array(arr1, n1);
    
    int arr2[] = {7};
    size_t n2 = sizeof(arr2) / sizeof(arr2[0]);
    reverse(arr2, n2);
    printf("Reverse array with n='%zu' is: ", n2);
    print_array(arr2, n2);
    
    int arr3[] = {1,2,3,4};
    size_t n3 = sizeof(arr3) / sizeof(arr3[0]);
    reverse(arr3, n3);
    printf("Reverse array with n='%zu' is: ", n3);
    print_array(arr3, n3);

    int arr4[] = {1,2,3,4,5};
    size_t n4 = sizeof(arr4) / sizeof(arr4[0]);
    reverse(arr4, n4);
    printf("Reverse array with n='%zu' is: ", n4);
    print_array(arr4, n4);

    return 0;
}
