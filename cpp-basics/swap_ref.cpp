#include <iostream>

void swap_ref(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

int check(const char *label, int got, int expected){
    if(got != expected){
        std::cout << label << " : FAIL; got " << got << " expected " << expected << std::endl;
        return 1;    
    }
    std::cout << label << " : PASS" << std::endl;
    return 0;
}

int main(void){
    
    int a = 5;
    int &b = a;
    swap_ref(a, b);
    int fail = check("Swap same variable - first variable a", a, 5);
    fail += check("Swap same variable - second variable b", b, 5);

    int x = 10;
    int y = -5;
    swap_ref(x,y);
    fail += check("Swap positive and negative - first variable x", x, -5);
    fail += check("Swap positive and negative - second variable y", y, 10);

    x = 7;
    y = 15;
    swap_ref(x,y);
    fail += check("Swap positives - first variable x", x, 15);
    fail += check("Swap positives - second variable y", y, 7);

    return fail != 0;
}
