#ifndef DRAM_H
#define DRAM_H
#include <stdlib.h>
#include <stdint.h>
//内存
#define MM_LEN 1000
uint8_t mm[MM_LEN]; //physical memory

// virtual address = 0x0 -> 0xffffffffffffffff
// physical address 000 -> 999
//mm[0x7ffffffee218 % MM_LEN];

#endif // DRAM_H
