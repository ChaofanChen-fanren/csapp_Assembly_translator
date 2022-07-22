#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include <stdlib.h>
#include <stdint.h>
#include "cpu/register.h"
#define NUM_INSTRTYPE 30

typedef enum OP
{
    mov_reg_reg,      //0
    mov_reg_mem,      //1
    mov_mem_reg,      //2
    push_reg,         //3
    pop_reg,          //4
    call,             //5
    ret,              //6
    add_reg_reg,      //7
}op_t;

typedef enum OD_TYPE
{
    EMPTY,
    IMM,REG,
    MM_IMM,MM_REG,MM_IMM_REG,MM_REG1_REG2,
    MM_IMM_REG1_REG2,MM_REG2_S,MM_IMM_REG2_S,
    MM_REG1_REG2_S,MM_IMM_REG1_REG2_S
} od_type_t;

typedef struct OD
{
    od_type_t type;

    int64_t imm; //有可能是负数
    uint64_t scal;
    uint64_t *reg1;
    uint64_t *reg2;

} od_t;

typedef struct INSTRUCT_STRUCT
{
    op_t op;
    od_t src;
    od_t dst;
    char code[100]; //运行命令可以看的更清楚一些
}inst_t;

//pointer pointing to the function 函数指针
typedef void(*handler_t)(uint64_t,uint64_t);
handler_t handler_table[NUM_INSTRTYPE];



static uint64_t decode_od(od_t od);//翻译操作数11类型的的方式
void instruction_cycle();//指令周期
void add_reg_reg_handler(uint64_t src,uint64_t dst);//add操作指令
void mov_reg_reg_handler(uint64_t src,uint64_t dst);//mov操作指令
void init_handler_table();//初始化handler_table

#endif // INSTRUCTION_H
