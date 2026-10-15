#include <stdio.h>
int main(void)
{
    float fahrenheit = 0.0f;
    printf("Celsius Fahrenheit Notes\n");
    for(int celsius=0; celsius<=100;celsius+=10){
        fahrenheit = celsius * 9.0 / 5 + 32;
        if(celsius == 0){
            printf("%7d %10.1f Freezing\n", celsius, fahrenheit);
        }
        else if(celsius == 100){
            printf("%7d %10.1f Boiling\n", celsius, fahrenheit);
        }
        else{
        printf("%7d %10.1f\n", celsius, fahrenheit);
        }
    }
return 0;
}
