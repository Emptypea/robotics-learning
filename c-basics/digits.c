#include <stdio.h>
int main(void){
    int num = 40731, sum = 0, len = 0, temp = num;

    while (temp != 0) {
        len++;
        sum += temp % 10;
        temp /= 10;
    }
    printf("Number: %d\n", num);
    printf("Number of digits: %d\n", len);
    printf("Sum of digits: %d\n", sum);
    return 0;
}
