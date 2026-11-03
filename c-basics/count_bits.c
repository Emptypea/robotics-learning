#include <stdio.h>
#include <stdint.h>

int count_bits(uint32_t x){
    int count = 0;
    for(int i=31; i>=0; i--){
        count += (x >> i) & 1u;
    }
    return count;
}


int main(void){
    uint32_t val1 = 0;
    uint32_t val2 = 0xFFFFFFFF;
    uint32_t val3 = 0xC5;
    uint32_t val4 = 1u << 31;

    printf("Number of bits with 1 in 0x%08x: %d\n", val1, count_bits(val1));
    printf("Number of bits with 1 in 0x%08x: %d\n", val2, count_bits(val2));
    printf("Number of bits with 1 in 0x%08x: %d\n", val3, count_bits(val3));
    printf("Number of bits with 1 in 0x%08x: %d\n", val4, count_bits(val4));

    return 0;
}
