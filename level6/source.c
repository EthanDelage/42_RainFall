#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void m(void);

void main(int argc, char **argv)
{
    char *dest;
    char *function_addr;

    dest = malloc(64);
    function_addr = malloc(4);
    *function_addr = &m;
    strcpy(dest, argv[1]);
    (*(void*)*function_addr)();
}

void n(void)
{
    system("/bin/cat /home/user/level7/.pass");
}

void m(void)
{
    printf("Nope");
}