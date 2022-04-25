#include "headers.h"
#include "bg_exit.h"

void fg(int job_number)
{

    struct bg *temp;
    temp = first;
    while (temp != NULL)
    {
        if (temp->job_number == job_number)
        {
            break;
        }
        temp = temp->next;
    }
    if (temp == NULL)
    {
        printf("This job number does not exist\n");
        return;
    }

    int pid = temp->pid;
    int pgid = getpgid(pid);
    // set the process to running
    delete (pid);
    signal(SIGTTOU, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    tcsetpgrp(STDIN_FILENO, pgid);
    fg_pid = pid;
    int stat;
    kill(pid, SIGCONT);
    waitpid(pgid, &stat, WUNTRACED);
    tcsetpgrp(STDIN_FILENO, getpgrp());
    signal(SIGTTOU, SIG_DFL);
    signal(SIGTTIN, SIG_DFL);
    if (WIFSTOPPED(stat))
    {
        insert_bg(fg_pid, name);
    }
}