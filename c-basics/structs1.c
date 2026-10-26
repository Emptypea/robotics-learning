#include <stdio.h>

struct Point {
    int x;
    int y;
};

void move_val(struct Point p){p.x += 10;}
void move_ptr(struct Point *p){p->x += 10;}

int main(void){
    struct Point a = {1, 2};
    struct Point b = a; // copy of a
    b.y = 50;
    printf("A: %d %d | %d %d\n", a.x, a.y, b.x, b.y);

    move_val(a);
    printf("B: %d %d\n", a.x, a.y);

    move_ptr(&a);
    printf("C: %d %d\n", a.x, a.y);

    return 0;
}
