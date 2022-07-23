#ifndef DRAM_H
#define DRAM_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

//内存
#define MM_LEN 1000000
uint8_t mm[MM_LEN]; //physical memory

// virtual address = 0x0 -> 0xffffffffffffffff
// physical address 000 -> 999
//mm[0x7ffffffee218 % MM_LEN];

uint64_t read64bits_dram(uint64_t paddr);
void write64bits_dram(uint64_t paddr,uint64_t data);
void print_register();
void print_stack();
#endif // DRAM_H
