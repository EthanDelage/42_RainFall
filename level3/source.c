#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint32_t m;

void main(void)
{
    v();
}

void v()
{
    char buf[520];

    fgets(buf, 512, stdin);
    printf(buf);
    if (m == 0x40)
    {
        printf("Wait what?!\n");
        system("/bin/sh");
    }
}