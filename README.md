### 实现一个汇编模拟器

#### **第4节**

**结构体**：

cpu 

- 寄存器
- 用union低地址实现rax,eax,ax,al,ah
- 只有一个cpu

memory

- 空间大小

instruction

- 操作符
- 源操作数
- 目操作数
- 操作符定义枚举类型 枚举add,mov等
- 

操作数

- 操作数类型 (操作数的11种枚举类型)
- 立即数
- 乘数
- 寄存器1
- 寄存器2
- 操作数类型解码函数 od_decode

##### **第五节**

改：

cpu结构体不是很对，改名为register结构体

立即数改为有符号数

reg1和reg2改为指针

实现：

1. 指令周期函数实现一部分
   - void instruction_cycle()；

2. 用函数指针数组实现操作符的相应的动作
   - void init_handler_table();
   - add_reg_reg_handler();
   - init_handler_table();

3. 简单的虚拟内存到物理内存的转化
   - uint64_t va2pa(uint64_t vaddr)
4. 指令操作数decode_od(od_t od)的实现
5. 操作数add_reg_reg_handler(uint64_t src,uint64_t dst)的实现

#### 第六节

改：

uint64_t decode_od(od_t od)中不能直接返回imm,考虑到imm为负数

char code[100];应该放在inst_t里面

实现：

1. 操作数类型的填充 OP
2. OD_TYPE增加EMPTY，表示对寄存器啥也不做
3. 汇编指令的填写 program
4. 寄存器和内存的初始化，然后指令运行后，通过与gdb的调试后看是否match框架搭建 （验证程序写的正确性）

#### 第七节

改：

elf指令填写错误

由于内存是1个字节编址，不能根据地址写来写8个字节，要用函数实现

实现：

1. 内存读写64位

   uint64_t read64bits_dram(uint64_t paddr);

   void write64bits_dram(uint64_t paddr,uint64_t data);

2. 打印相关寄存器和内存的信息

   void print_register();

   void print_stack();

3. 实现call指令和mov指令

   void mov_reg_reg_handler(uint64_t src,uint64_t dst);//mov操作指令

   void call_handler(uint64_t src,uint64_t dst);//call操作指令

4. 成功调试好运行三条指令

#### 第八节

改：decode_od解码返回值改为地址

实现：

1. 指令 push
   - void push_reg_handler(uint64_t src,uint64_t dst);//push指令
2. 实现指令mov_reg_mem
   - void mov_reg_mem_handler(uint64_t src,uint64_t dst); //mov指令


#### 第九节

- 实现MOV PUSH POP RET CALL ADD指令 
- 第一次重构代码

```c
//convert.c
string2uint();//covert string to int64_t
uint32_t uint2float(uint32_t u);//convert uint32_t to its float

/******************************************************************/
//printf.c 调试打印
uint64_t debug_printf(uint64_t open_set, const char *format, ...);// wrapper of stdio printf

/******************************************************************/
//isa.c  //指令集处理
//op_t,od_type_t,od_t,inst_t 
static void parse_instruction(const char *str, inst_t *inst, core_t *cr);//处理汇编字符串，指令的翻译
static void parse_operand(const char *str, od_t *od, core_t *cr);//操作数的翻译
static uint64_t decode_operand(od_t *od);//返回操作数的数字
//各种指令集的函数
static void mov_handler             (od_t *src_od, od_t *dst_od, core_t *cr);
static void push_handler            (od_t *src_od, od_t *dst_od, core_t *cr);
static void pop_handler             (od_t *src_od, od_t *dst_od, core_t *cr);
static void leave_handler           (od_t *src_od, od_t *dst_od, core_t *cr);
static void call_handler            (od_t *src_od, od_t *dst_od, core_t *cr);
static void ret_handler             (od_t *src_od, od_t *dst_od, core_t *cr);
static void add_handler             (od_t *src_od, od_t *dst_od, core_t *cr);
static void sub_handler             (od_t *src_od, od_t *dst_od, core_t *cr);
static void cmp_handler             (od_t *src_od, od_t *dst_od, core_t *cr);
static void jne_handler             (od_t *src_od, od_t *dst_od, core_t *cr);
static void jmp_handler             (od_t *src_od, od_t *dst_od, core_t *cr);
static inline void reset_cflags(core_t *cr); //四个符号CF ,ZF , SF ,OF的清零
static inline void next_rip(core_t *cr); // PC + 1;
void instruction_cycle(core_t *cr);//负责执行指令周期
void print_register(core_t *cr);//打印寄存器
void print_stack(core_t *cr);//打印的栈的周围的数据

/******************************************************************/
//mmu.c 内存管理
uint64_t va2pa(uint64_t vaddr,core_t *cr);// 虚拟地址转化为物理地址


/******************************************************************/
//dram.c  DRAM 内存读写
uint64_t read64bits_dram(uint64_t paddr,core_t *cr); //一次性读64位
void write64bits_dram(uint64_t paddr, uint64_t data, core_t *cr);//一次性写64位
```

`common.h` 

1. 设置一些好读的debug宏定义
2. 一些要常见处理的函数定义

`cpu.h`

1. 把csapp的所有的寄存器都设置了
2. Program counter 从寄存器里面分开 与 四个flag放在一起
3. 增加了多核处理的扩充条件

`memory.h`

1. 设置内存的大小为65536字节
2. 内存读写的定义函数

`main_hardware.c`

1. 测试递归调用加法函数指令是否与gdb的运行一样
