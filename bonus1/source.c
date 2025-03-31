#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int value;
    char buf[40];

    value = atoi(argv[1]);
    if (value < 10)
    {
        memcpy(buf, argv[2], value * 4);
        if (value == 0x574f4c46)
        {
            execl("/bin/sh", "sh", 0);
        }
        value = 0;
    } else
    {
        value = 1;
    }
    return value;
}
