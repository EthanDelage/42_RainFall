#include <stdio.h>
#include <stdlib.h>

void main(void)
{
    char buf[76];

    gets(buf);
}

void run(void)
{
    printf("Good... Wait what?\n");
    system("/bin/sh");
}