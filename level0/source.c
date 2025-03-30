#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int n;
    uid_t uid;
    gid_t gid;
    char *sh_path;

    n = atoi(argv[1]);
    if (n == 423) {
        sh_path = strdup("/bin/sh");
        uid = geteuid();
        gid = getegid();
        setreuid(uid, uid);
        setregid(gid, gid);
        execve("/bin/sh", &sh_path, NULL);
    } else
    {
        dprintf(STDOUT_FILENO, "No !\n");
    }
    return 0;
}