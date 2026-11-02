#include <stdio.h>
#include <stdint.h>

uint32_t set_bit(uint32_t x, unsigned n){
    return x | (1u << n );
}

uint32_t clear_bit(uint32_t x, unsigned n){
    return x &(~(1u << n));
}

uint32_t toggle_bit(uint32_t x, unsigned n){
    return x ^ (1u << n);
}

int test_bit(uint32_t x, unsigned n){
    return (x >> n) & 1u;
}

void print32(const char *label, uint32_t x){
    printf("%-28s\t", label);
    for(int i = 31; i >= 0; i--){
        putchar(((x >> i) & 1u) ? '1' : '0');
        if((i % 4 == 0) && (i != 0)){printf(" ");}
    }

    printf("  0x%08x\n", x);
}


int main(void){
    uint32_t set_1 = set_bit(0x00000000, 0);
    print32("set_bit(0x00000000, 0)", set_1);

    uint32_t set_2 = set_bit(0x00000000, 31);
    print32("set_bit(0x00000000, 31)", set_2);

    uint32_t set_3 = set_bit(0x0000000A, 1);
    print32("set_bit(0x0000000A, 1)",set_3);

    uint32_t clear_1 = clear_bit(0x0000000F, 0);
    print32("clear_bit(0x0000000F, 0)",clear_1);

    uint32_t clear_2 = clear_bit(0xFFFFFFFF, 31);
    print32("clear_bit(0xFFFFFFFF, 31)",clear_2);

    uint32_t clear_3 = clear_bit(0x0000000A, 2);
    print32("clear_bit(0x0000000A, 2)",clear_3);

    uint32_t toggle_1 = toggle_bit(0x0000000A, 2);
    print32("toggle_bit(0x0000000A, 2)",toggle_1);

    uint32_t toggle_2 = toggle_bit(toggle_bit(0x0000000A, 2), 2);
    print32("toggle_bit(toggle_bit(0x0000000A, 2), 2)",toggle_2);

    int test_1 = test_bit(0x80000000, 31);
    printf("%-28s %d\n", "test_bit(0x80000000, 31)", test_1);

    int test_2 = test_bit(0x0000000A, 0);
    printf("%-28s %d\n", "test_bit(0x0000000A, 0)", test_2);

    return 0;
}
