#include "cpu/register.h"
#include <stdio.h>
#include <stdint.h>
#include "memory/instruction.h" 
#include "disk/elf.h"
#include "memory/dram.h"

int main()
{
    // reg.rax = 0x0123456789abcdef;

    // printf("eax: %08x\n",reg.eax);
    // printf("ax: %04x\n",reg.ax);
    // printf("ah: %02x\n",reg.ah);
    // printf("al: %02x\n",reg.al);

    //初始化所有操作符对应动作的函数
    init_handler_table();
    //比较gdb所有的寄存器和栈
    reg.rax = 0x12340000;
    reg.rbx = 0x0;
    reg.rcx = 0x8000660;
    reg.rdx = 0xabcd;
    reg.rsi = 0x7ffffffee2f8;
    reg.rdi = 0x1;
    reg.rbp = 0x7ffffffee210;
    reg.rsp = 0x7ffffffee1f0;

    reg.rip = (uint64_t)&program[11];  //程序开始的地方
    

    mm[va2pa(0x7ffffffee210)] = 0x08000660;  //rbp
    mm[va2pa(0x7ffffffee20f)] = 0x0;
    mm[va2pa(0x7ffffffee200)] = 0xabcd;
    mm[va2pa(0x7ffffffee1ff)] = 0x12340000;
    mm[va2pa(0x7ffffffee1f0)] = 0x08000060; //rsp

    //run inst
    for(int i = 0;i < 15;i++){
        instruction_cycle();
    }

    //verify
    int match = 1;

    match = match && (reg.rax == 0x1234abcd);
    match = match && (reg.rbx == 0x0);
    match = match && (reg.rcx == 0x8000660);
    match = match && (reg.rdx == 0x12340000);
    match = match && (reg.rsi == 0xabcd);
    match = match && (reg.rdi == 0x12340000);
    match = match && (reg.rbp == 0x7ffffffee210);
    match = match && (reg.rsp == 0x7ffffffee1f0);


    if(match == 1){
        printf("register match\n");
    }else{
        printf("register not match\n");
    }


    match = match && ( mm[va2pa(0x7ffffffee210)] == 0x08000660);
    match = match && ( mm[va2pa(0x7ffffffee20f)] == 0x1234abcd);
    match = match && ( mm[va2pa(0x7ffffffee200)] == 0xabcd);
    match = match && ( mm[va2pa(0x7ffffffee1ff)] == 0x12340000);
    match = match && ( mm[va2pa(0x7ffffffee1f0)] == 0x08000060);

    if(match == 1){
        printf("memory match\n");
    }else{
        printf("memory not match\n");
    }

    return 0;
}