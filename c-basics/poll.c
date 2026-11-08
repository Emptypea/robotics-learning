#include <stdint.h>

uint32_t status_bit = 0;
volatile uint32_t vstatus_bit = 0;

void wait_plain(void) {  while((status_bit & 1u) == 0) { } }

void wait_volatile(void) { while((vstatus_bit & 1u) == 0) { } }
