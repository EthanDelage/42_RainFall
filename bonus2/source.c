#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int language = 0;

int main(int argc, char **argv)
{
    char buf[72];
    char *lang;

    if (argc != 3)
    {
        return 1;
    }
    memset(buf, '\0', 72);
    strncpy(buf, argv[1], 40);
    strncpy(&buf[40], argv[2], 32);
    lang = getenv("LANG");
    if (lang != NULL)
    {
        if (memcmp(lang, "fi", 2) == 0)
        {
            language = 1;
        } else if (memcmp(lang, "nl", 2) == 0)
        {
            language = 2;
        }
    }
    greetuser(buf);
    return 0;
}

void greetuser(char *buf)
{
    char str[64];

    if (language == 1)
    {
        strcpy(str, "Hyvää päivää ");
    } else if (language == 2)
    {
        strcpy(str, "Goedemiddag! ");
    } else if (language == 0)
    {
        strcpy(str, "Hello ");
    }
    strcat(str, buf);
    puts(str);
}
