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

改：cpu结构体不是很对，改名为register结构体

立即数改为有符号数，reg1和reg2改为指针

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
