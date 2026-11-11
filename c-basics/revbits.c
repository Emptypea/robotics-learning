#include <stdio.h>
#include <stdint.h>

uint32_t reverse_bits(uint32_t x){
    uint32_t res = 0;
    for(int count = 0; count <= 31; count++){
        unsigned shift_read = 31 - count;
        unsigned shift_write = count;

        uint32_t read = (x >> shift_read) & 1u;
        res |= (read << shift_write);
    }

    return res;
}

int check(const char* label, uint32_t got, uint32_t expected){
    if(got != expected){
        printf("%-28s\tFAIL: got 0x%08x, expected 0x%08x\n", label, got, expected);
        return 1;
    }
    printf("%-28s\tPASS\n", label);
    return 0;
}

int main(void){
    int err = 0;

    uint32_t reg = 1u;
    err += check("Bit 0 is 1", reverse_bits(reg), 0x80000000);

    reg = 0x80000000;
    err += check("Bit 31 is 1", reverse_bits(reg), 1u);

    reg = 0xFFFF0000;
    err += check("Half are 1s", reverse_bits(reg), 0x0000FFFF);

    reg = 0x12345678;
    err += check("Mixed Bits", reverse_bits(reg), 0x1E6A2C48);

    reg = 0x00000000;
    err += check("all 0s", reverse_bits(reg), 0x00000000);

    reg = 0x00000006;
    err += check("Asymmetric 6", reverse_bits(reg), 0x60000000);

    reg = 0x66666666;
    err += check("All 6s", reverse_bits(reg), 0x66666666);

    reg = 0xFFFFFFFF;
    err += check("All 1s", reverse_bits(reg), 0xFFFFFFFF);

    if(err != 0){
        printf("FAIL\n");
    }
    else{
        printf("All cases : PASS\n");
    }

    return err != 0;
}
