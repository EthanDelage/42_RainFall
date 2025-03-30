#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char c[0x44];

int main(int argc, char **argv)
{
    char **buf1;
    char *buf2;
    char **buf3;
    FILE *stream;

    buf1 = malloc(8);
    *buf1 = 1;
    buf2 = malloc(8);
    buf1[1] = buf2;
    buf3 = malloc(8);
    *buf3 = 2;
    buf2 = malloc(8);
    buf3[1] = buf2;
    strcpy(buf1[1], argv[1]);
    strcpy(buf3[1], argv[2]);
    stream = fopen("/home/user/level8/.pass", "r");
    fgets(c, 0x44, stream);
    puts("~~");
    return 0;
}

void m(void)
{
    time_t tVar;
    tVar = time(NULL);
    printf("%s - %d\n", c, tVar);
}
