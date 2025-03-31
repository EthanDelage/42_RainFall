#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
    char buf[54];

    pp(buf);
    puts(buf);
    return 0;
}

void pp(char *buf)
{
    char str1[20];
    char str2[20];
    size_t len;

    p(str1, " - ");
    p(str2, " - ");
    strcpy(buf, str1);
    len = strlen(buf);
    buf[len] = ' ';
    buf[len+1] = '\0';
    strcat(buf, str2);
}

void p(char *dest, char *str)
{
    char *res;
    char buf[4104];

    puts(str);
    read(0, buf, 4096);
    res = strchr(buf, '\n');
    *res = '\0';
    strncpy(dest, buf, 20);
}