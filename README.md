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

第八节

改：decode_od解码返回值改为地址

实现：

1. 指令 push
   - void push_reg_handler(uint64_t src,uint64_t dst);//push指令
2. 实现指令mov_reg_mem
   - void mov_reg_mem_handler(uint64_t src,uint64_t dst); //mov指令
