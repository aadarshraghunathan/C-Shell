#include "headers.h"

void pinfo(int pid)
{

    int parent_id;
    if (pid == -1)
    {
        pid = getpid();
    }
    char filename[1000];
    FILE *fp;
    sprintf(filename, "/proc/%d/stat", pid);
    fp = fopen(filename, "r");
    char proc[52][1000];

    fscanf(fp, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s", proc[0], proc[1], proc[2], proc[3], proc[4], proc[5], proc[6], proc[7], proc[8], proc[9], proc[10], proc[11], proc[12], proc[13], proc[14], proc[15], proc[16], proc[17], proc[18], proc[19], proc[20], proc[21], proc[22], proc[23], proc[24], proc[25], proc[26], proc[27], proc[28], proc[29], proc[30], proc[31], proc[32], proc[33], proc[34], proc[35], proc[36], proc[37], proc[38], proc[39], proc[40], proc[41], proc[42], proc[43], proc[44], proc[45], proc[46], proc[47], proc[48], proc[49], proc[50], proc[51]);

    pid_t terminal = tcgetpgrp(STDIN_FILENO);
    pid_t pg_id = getpgid(pid);

    printf("pid -- %s\n", proc[0]);
    if (terminal == pg_id)
    {
        printf("Process Status -- %s+\n", proc[2]);
    }
    else
    {
        printf("Process Status -- %s\n", proc[2]);
    }
    printf("%s\n", proc[1]);
    printf("memory -- %s\n", proc[22]);

    fclose(fp);
}
