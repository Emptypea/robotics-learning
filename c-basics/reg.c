#include <stdio.h>
#include <stdint.h>

// Simulating a register with 3 fields: PRESCALE(bits 11...8), MODE(bits 3..1), ENABLE(bit 0)

#define EN_SHIFT 0
#define MODE_SHIFT 1
#define PRESCALE_SHIFT 8

#define EN_MASK (1u << EN_SHIFT)                /* 0x00000001 */
#define MODE_MASK (7u << MODE_SHIFT)            /* 0x0000000E */
#define PRESCALE_MASK (15u << PRESCALE_SHIFT)   /* 0x00000F00 */

uint32_t field_read(uint32_t reg, uint32_t mask, unsigned shift){
    return (reg & mask) >> shift;
}

uint32_t field_write(uint32_t reg, uint32_t mask, unsigned shift, uint32_t value){
    return (reg & ~mask) | ((value << shift) & mask);
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
    uint32_t reg;

    // TEST 1: EN set to 1, starting from 0x00000000
    reg = 0x00000000;
    reg = field_write(reg, EN_MASK, EN_SHIFT, 1);

    err += check("TEST 1: EN set - ", reg, 0x00000001);

    // TEST 2: EN clear to 0, starting from 0xFFFFFFFF
    reg = 0xFFFFFFFF;
    reg = field_write(reg, EN_MASK, EN_SHIFT, 0);

    err += check("TEST 2: EN clear - ", reg, 0xFFFFFFFE);

    // TEST 3: MODE = 7(max), starting from 0x00000000
    reg = 0x00000000;
    reg = field_write(reg, MODE_MASK, MODE_SHIFT, 7);

    err += check("TEST 3: MODE = 7 - ", reg, 0x0000000E);

    // TEST 4: MODE = 0, starting from 0xFFFFFFFF
    reg = 0xFFFFFFFF;
    reg = field_write(reg, MODE_MASK, MODE_SHIFT, 0);

    err += check("TEST 4: MODE = 0 - ", reg, 0xFFFFFFF1);

    // TEST 5: MODE = 10(too large), starting from 0x00000000
    reg = 0x00000000;
    reg = field_write(reg, MODE_MASK, MODE_SHIFT, 10);

    err += check("TEST 5: MODE = 10 - ", reg, 0x00000004);

    // TEST 6: MODE = 5, starting from 0xFFFFFFFF
    reg = 0xFFFFFFFF;
    reg = field_write(reg, MODE_MASK, MODE_SHIFT, 5);

    err += check("TEST 6: MODE = 5 - ", reg, 0xFFFFFFFB);

    // TEST 7: field_read Prescale, starting from 0x00000A0B
    reg = 0x00000A0B;
    uint32_t read_prescale = field_read(reg, PRESCALE_MASK, PRESCALE_SHIFT);

    err += check("TEST 7: PRESCALE read", read_prescale, 0xA);

    // TEST 8: Write-then-read Prescale, starting from 0x00000000
    reg = 0x00000000;
    reg = field_write(reg, PRESCALE_MASK, PRESCALE_SHIFT, 0xC);

    read_prescale = field_read(reg, PRESCALE_MASK, PRESCALE_SHIFT);

    err += check("TEST 8: PRESCALE write-then-read", read_prescale, 0xC);


    // TEST 9: Chained test, starting from 0x00000000, set EN=1, MODE=5, PRESCALE=0xD
    reg = 0x00000000;
    reg = field_write(reg, EN_MASK, EN_SHIFT, 1);
    err += check("TEST 9: EN set - ", reg, 0x00000001);

    reg = field_write(reg, MODE_MASK, MODE_SHIFT, 5);
    err += check("TEST 9: MODE set - ", reg, 0x0000000B);

    reg = field_write(reg, PRESCALE_MASK, PRESCALE_SHIFT, 0xD);
    err += check("TEST 9: PRESCALE set - ", reg, 0x00000D0B);

    printf("\n-----------------------------------\n");

    if(err == 0){
        printf("All tests passed!\n");
    } else {
        printf("%d test(s) failed!\n", err);
    }

    return err != 0;
}
