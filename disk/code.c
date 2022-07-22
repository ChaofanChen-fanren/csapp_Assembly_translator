//代码一般在磁盘上 然后加载到内存里的
#include <stdlib.h>
#include <stdint.h>
#include "memory/instruction.h"
//指令的存储
#define INST_LEN 100
inst_t program[INST_LEN] = {
    // {
    //     mov,
    //     {REG,0,0,(uint64_t *)& reg.rax,NULL},
    //     {REG,0,0,(uint64_t *)& reg.rbx,NULL},
    //     "mov rax rbx"
    // },
};
