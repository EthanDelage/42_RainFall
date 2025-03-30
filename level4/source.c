#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint32_t m;

void main(void)
{
    n();
}

void n(void)
{
    char buf[520];

    fgets(buf, 512, stdin);
    p(buf);
    if (m == 16930116)
    {
        system("/bin/cat /home/user/level5/.pass");
    }
}

void p(char *format)
{
    printf(format);
}