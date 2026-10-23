#include <stdio.h>

int main(void) {

    char s[] = "robot";
    
    printf("%zu\n", sizeof s);   // P1
    
    printf("%c\n", s[2]);        // P2
    
    printf("%d\n", s[5]);        // P3
    
    s[3] = '\0';
    
    printf("%s\n", s);           // P4
    
    printf("%zu\n", sizeof s);   // P5

    return 0;
}
