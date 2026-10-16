#include <stdio.h>

// size of array must be greater than 0
int array_max(int arr[], int size){
    int max = arr[0];
    for(int i=1; i<size; i++){
        if(arr[i] > max){
            max = arr[i];
        }
    }
    return max;
}

// size of array must be greater than 0
double array_max_2(double arr[], int size){
    double max = arr[0];
    for(int i=1; i<size; i++){
        if(arr[i] > max){
            max = arr[i];
        }
    }
    return max;
}

// size of array must be greater than 0
int array_min(int arr[], int size){
    int min = arr[0];
    for(int i=1; i<size; i++){
        if(arr[i] < min){
            min = arr[i];
        }
    }
    return min;
}

double array_avg(int arr[], int size){
    double sum = 0;
    for(int i=0; i<size; i++){
        sum += arr[i];
    }
    return sum / size;
}

int main(void){
    int arr[] = {23, 25, 30, 22, 28, 24};
    int size = sizeof(arr) / sizeof(arr[0]);

    int cold[]= {-5, -3, -10, -1};
    int size2 = sizeof(cold) / sizeof(cold[0]);

    double arr3[] = {1.5, 2.5, 3.5, 4.5, 5.5};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);

    printf("Max: %d\n", array_max(arr, size));
    printf("Min: %d\n", array_min(arr, size));
    printf("Avg: %.2f\n", array_avg(arr, size));

    printf("Cold temperature Max: %d\n", array_max(cold, size2));
    printf("Cold temperature Min: %d\n", array_min(cold, size2));
    printf("Cold temperature Avg: %.2f\n", array_avg(cold, size2));

    printf("Double type array Max: %.2f\n", array_max_2(arr3, size3));
    printf("Size of double array: %zu\n", sizeof(arr3));
    printf("Size of double array element: %zu\n", sizeof(arr3[0]));

    return 0;
}