#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(void)
{
    p();
}

void p(void)
{
    uint32_t retaddr;
    char buf[76];

    fflush(stdout);
    gets(buf);
    retaddr = __builtin_return_address(0);
    if ((retaddr & 0xb0000000) == 0xb0000000)
    {
        printf("(%p)\n", (void*) retaddr);
        exit(1);
    }
    puts(buf);
    strdup(buf);
}