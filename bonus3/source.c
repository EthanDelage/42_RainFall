#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    FILE *stream;
    int value;
    char buf[132];

    stream = fopen("/home/user/end/.pass", "r");
    memset(buf, '\0', 132);
    if (stream == NULL || argc != 2)
    {
        return -1;
    }
    fread(buf, 1, 66, stream);
    buf[65] = '\0';
    value = atoi(buf);
    buf[value] = '\0';
    fread(&buf[66], 1, 65, stream);
    fclose(stream);
    if (strcmp(buf, argv[1]) == 0)
    {
        execl("/bin/sh", "sh", 0);
    } else
    {
        puts(&buf[66]);
    }
    return 0;
}
