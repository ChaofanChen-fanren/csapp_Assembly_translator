#ifndef REGISTER_H
#define REGISTER_H
#include <stdlib.h>
#include <stdint.h>

typedef struct  CPU_STRUCT
{
    union //共享低地址
    {
        struct
        {
            uint8_t al;
            uint8_t ah;
        };
        uint16_t ax;
        uint32_t eax;
        uint64_t rax;
    };
    u_int64_t rbx;
    u_int64_t rcx;
    u_int64_t rdx;
    u_int64_t rsi;
    u_int64_t rdi;
    u_int64_t rbp;
    u_int64_t rsp;

    
    u_int64_t rip;
}cpu_t;

cpu_t cpu; //只有一个cpu

#endif // REGISTER_H
