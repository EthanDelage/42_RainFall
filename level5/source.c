#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void main(void)
{
    n();
}

void n(void)
{
    char buf[520];

    fgets(buf, 512, stdin);
    printf(buf);
    exit(1);
}

void o(void)
{
    system("/bin/sh");
    _exit(1);
}