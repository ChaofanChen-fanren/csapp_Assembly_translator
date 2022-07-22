#include "cpu/register.h"
#include <stdio.h>

int main()
{
    
    
    cpu.rax = 0x0123456789abcdef;

    printf("eax: %08x\n",cpu.eax);
    printf("ax: %04x\n",cpu.ax);
    printf("ah: %02x\n",cpu.ah);
    printf("al: %02x\n",cpu.al);
   

    return 0;
}
