#include <stdio.h>
#include <stdint.h>

static int is_pow2(uint32_t x){
    return x != 0 && (x & (x - 1)) == 0;
}

static int check(const char *label, uint32_t calc, uint32_t expected){
    if (calc != expected){
        printf("FAIL: %s got 0x%08X, expected 0x%08X\n", label, calc, expected);
        return 1;
    }
    printf("PASS: %s got 0x%08X, expected 0x%08X\n", label, calc, expected);
    return 0;
}

int main(void){
    int err = 0;

    // TEST 1: Check if 0 is a power of 2
    err += check("TEST 1: is_pow2(0) - ", is_pow2(0), 0);

    // TEST 2: Check if 1 is a power of 2
    err += check("TEST 2: is_pow2(1) - ", is_pow2(1), 1);

    // TEST 3: Check if 2 is a power of 2
    err += check("TEST 3: is_pow2(2) - ", is_pow2(2), 1);

    // TEST 4: Check if 8 is a power of 2
    err += check("TEST 4: is_pow2(8) - ", is_pow2(8), 1);

    // TEST 5: Check if 12 is a power of 2
    err += check("TEST 5: is_pow2(12) - ", is_pow2(12), 0);

    // TEST 6: Check if 0x80000000 is a power of 2
    err += check("TEST 6: is_pow2(0x80000000) - ", is_pow2(0x80000000), 1);

    // TEST 7: Check if 0xFFFFFFFF is a power of 2
    err += check("TEST 7: is_pow2(0xFFFFFFFF) - ", is_pow2(0xFFFFFFFF), 0);

    // TEST 8: Check if 0x80000001 is a power of 2
    err += check("TEST 8: is_pow2(0x80000001) - ", is_pow2(0x80000001), 0);

    return err != 0;
}
