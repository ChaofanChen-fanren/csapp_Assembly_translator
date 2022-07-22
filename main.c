#include "cpu/register.h"
#include <stdio.h>

int main()
{
    
    
    reg.rax = 0x0123456789abcdef;

    printf("eax: %08x\n",reg.eax);
    printf("ax: %04x\n",reg.ax);
    printf("ah: %02x\n",reg.ah);
    printf("al: %02x\n",reg.al);
   

    return 0;
}
