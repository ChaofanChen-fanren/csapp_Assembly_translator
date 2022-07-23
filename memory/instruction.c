#include "memory/instruction.h"
#include "cpu/mmu.h"
#include "memory/dram.h"
#include <stdio.h>

uint64_t decode_od(od_t od)
{
    if(od.type == IMM)
    {
        return *((uint64_t *)&od.imm); //输出内存的布局,因为imm为有符号数
    }else if (od.type == REG){
        //返回寄存器地址 
        return (uint64_t)od.reg1;
    }else{

        //mm
        uint64_t vaddr = 0;
        if(od.type == MM_IMM){
            //vaddr = od.imm;
            vaddr = *((uint64_t *)&od.imm);
        }else if(od.type == MM_REG){

            vaddr = *(od.reg1);
        }else if(od.type == MM_IMM_REG){

            vaddr = od.imm + *(od.reg1);
        }else if(od.type == MM_REG1_REG2){

            vaddr = *(od.reg1) + *(od.reg2);
        }else if(od.type == MM_IMM_REG1_REG2){

            vaddr = od.imm + *(od.reg1) + *(od.reg2);
        }else if(od.type == MM_REG2_S){
            vaddr = (*(od.reg2))*od.scal;

        }else if(od.type == MM_IMM_REG2_S){

            vaddr = od.imm + (*(od.reg2)) * od.scal;
        }else if(od.type == MM_REG1_REG2_S){

            vaddr =*(od.reg1) +  (*(od.reg2)) * od.scal;
        }else if(od.type == MM_IMM_REG1_REG2_S){

            vaddr =  od.imm + *(od.reg1) +  (*(od.reg2)) * od.scal;
        }
        return va2pa(vaddr);
    }
}


void instruction_cycle()
{
    //取指令
    inst_t *instr = (inst_t *)reg.rip;

    //解析操作数
    //imm:imm
    //reg:value
    //mm:paddr
    uint64_t src = decode_od(instr->src);
    uint64_t dst = decode_od(instr->dst);

    // function_t func = function_table[instr->op];
    // func(src,dst);
    //add rax rbx
    //op = add_reg_reg = 3 
    //handler_table[op] -> handler_table[3] == add_reg_reg_handler
    
    handler_t handler = handler_table[instr->op];  //add_reg_reg_handler

    // add_reg_reg_handler(src = &rax,dst = &rbx)
    handler(src,dst);
    printf("    %s\n",instr->code);
    
}
void init_handler_table()
{
    handler_table[mov_reg_reg] = &mov_reg_reg_handler;
    handler_table[add_reg_reg] = &add_reg_reg_handler;
    handler_table[call] = &call_handler;
}
void add_reg_reg_handler(uint64_t src,uint64_t dst)
{
    // add_reg_reg_handler(src = &rax,dst = &rbx)
    /** 
     * rax pmm[0x1234] = 0x12340000
     * rbx pmm[0x1235] = 0xabcd
     * 
     * src:0x1234
     * dst:0x1235
     * 
     *   *(uint64_t *)src = 0x12340000
     *   *(uint64_t *)dst = 0xabcd
     *   0x12340000 + 0xabcd = 0x1234abcd
     */
    *(uint64_t *)dst = *(uint64_t *)dst + *(uint64_t *)src;
    reg.rip = reg.rip + sizeof(inst_t); //PC+1
}
void call_handler(uint64_t src,uint64_t dst)//call操作指令
{   
    //src: imm address of called function
    //stcak point - 8;
    reg.rsp = reg.rsp - 8;

    //write return address to rsp memory
    write64bits_dram(
        va2pa(reg.rsp),
        reg.rip + sizeof(inst_t)
    );

    reg.rip = src;
}

void mov_reg_reg_handler(uint64_t src,uint64_t dst)//mov操作指令
{
    /**
     * src :reg
     * dst :reg
     * 
     */
    *((uint64_t *)dst) = *((uint64_t *)src);
    reg.rip = reg.rip + sizeof(inst_t); //PC+1
}
