#include <stdio.h>

size_t my_strlen(const char *s){
    const char *temp = s;
    while(*temp != '\0'){
        temp++;
    }
    return temp - s;
}

int main(void) {
    char str1[] = "";
    size_t len1 = my_strlen(str1);
    printf("Length of the string \"%s\" is: %zu\n", str1, len1);

    char str2[] = "a";
    size_t len2 = my_strlen(str2);
    printf("Length of the string \"%s\" is: %zu\n", str2, len2);

    char str3[] = "robot";
    size_t len3 = my_strlen(str3);
    printf("Length of the string \"%s\" is: %zu\n", str3, len3);

    str3[3] = '\0';
    size_t len4 = my_strlen(str3);
    printf("Length of the string \"%s\" is: %zu\n", str3, len4);

    char str4[100] = "cat";
    size_t len5 = my_strlen(str4);
    printf("Length of the string \"%s\" is: %zu\n", str4, len5);

    return 0;
}
