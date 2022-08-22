#include <stdint.h>
#include <stdlib.h>
#include <headers/linker.h>
#include <headers/common.h>
#include <stdio.h>


// void test_read_elf()
// {
//     char buf[MAX_ELF_FILE_LENGTH][MAX_ELF_FILE_WIDTH];
//     int count = read_elf("./files/exe/sum.elf.txt", (uint64_t)buf);
//     for (int i = 0; i < count;i++){
//         printf("%s\n", buf[i]);
//     }
// }

void test_link_elf()
{
    elf_t src[2];
    parse_elf("./files/exe/sum.elf.txt", &src[0]);
    parse_elf("./files/exe/main.elf.txt", &src[1]);

    elf_t dst;
    elf_t *srcp[2];
    srcp[0] = &src[0];
    srcp[1] = &src[1];
    link_elf((elf_t **)&srcp, 2, &dst);
    
    
    
    //write_eof("./files/exe/output.eof.txt", &dst);

    free_elf(&src[0]);
    free_elf(&src[1]);
    free_elf(&dst);
    //finally_cleanup();
}
int main()
{

    test_link_elf();
    return 0;
}
