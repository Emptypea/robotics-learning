#include <stdio.h>

int countDigits(int num) {
    if(num == 0) {
        return 1; // Special case for 0
    }
    int count = 0;
    while (num != 0) {
        count++;
        num /= 10;
    }
    return count;
}

int sumDigits(int num) {
    int sum = 0;
    while (num != 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}


int main(void){

    int number;
    printf("Enter a number: ");
    scanf("%d", &number);

    int digitCount = countDigits(number);
    int digitSum = sumDigits(number);

    printf("Number of digits: %d\n", digitCount);
    printf("Sum of digits: %d\n", digitSum);

    return 0;

}
