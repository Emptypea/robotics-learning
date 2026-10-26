#include <stdio.h>

int sum_range(const int *begin, const int *end) {
    int sum = 0;
    while (begin < end) {
        sum += *begin;
        begin++;
    }
    return sum;
}

int main(void) {
    int arr[] = {3, 1, 4, 1, 5};

    int total1 = sum_range(arr, arr);
    printf("sum of empty range: %d\n", total1);

    int total2 = sum_range(arr, arr + 1);
    printf("sum of first element: %d\n", total2);

    int total3 = sum_range(arr, arr + 5);
    printf("sum of all elements: %d\n", total3);

    int total4 = sum_range(arr + 1, arr + 4);
    printf("sum of middle elements: %d\n", total4);

    return 0;
}
