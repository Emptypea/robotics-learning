#include <stdio.h>

int remove_duplicates(int *arr, int size){

    if(size == 0 || size == 1){
        return size;
    }
    int i=0, j=i+1;
    while(j<size){
        if(arr[i] == arr[j]){
            j++;
        }
        else{
            i++;
            arr[i] = arr[j];
            j++;
        }   
    }
    return i + 1;
}

void prints_array(int *arr, int size){
    if(size == 0){
        printf("Empty Array\n");
        return;
    }
    printf("Array: ");
    for(int i=0; i<size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");

}

int main(void){
    
    int arr1[] = {1, 1, 2};
    int arr2[] = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
    int arr3[] = {7};
    int arr4[] = {1, 2, 3, 4, 5};
    int arr5[] = {1, 1, 1, 1, 1};
    int arr6[] = {1, 2, 3, 4, 4, 4};

    int size1 = sizeof(arr1)/sizeof(arr1[0]);
    int size2 = sizeof(arr2)/sizeof(arr2[0]);
    int size3 = sizeof(arr3)/sizeof(arr3[0]);
    int size4 = sizeof(arr4)/sizeof(arr4[0]);
    int size5 = sizeof(arr5)/sizeof(arr5[0]);
    int size6 = sizeof(arr6)/sizeof(arr6[0]);

    int unique0 = remove_duplicates(NULL, 0);
    int unique1 = remove_duplicates(arr1, size1);
    int unique2 = remove_duplicates(arr2, size2);
    int unique3 = remove_duplicates(arr3, size3);
    int unique4 = remove_duplicates(arr4, size4);
    int unique5 = remove_duplicates(arr5, size5);
    int unique6 = remove_duplicates(arr6, size6);

    prints_array(NULL, unique0);
    printf("Unique elements in arr: %d\n", unique0);

    prints_array(arr1, unique1);
    printf("Unique elements in arr1: %d\n", unique1);

    prints_array(arr2, unique2);
    printf("Unique elements in arr2: %d\n", unique2);

    prints_array(arr3, unique3);
    printf("Unique elements in arr3: %d\n", unique3);

    prints_array(arr4, unique4);
    printf("Unique elements in arr4: %d\n", unique4);

    prints_array(arr5, unique5);
    printf("Unique elements in arr5: %d\n", unique5);

    prints_array(arr6, unique6);
    printf("Unique elements in arr6: %d\n", unique6);

    return 0;
    
}