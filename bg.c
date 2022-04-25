#include "headers.h"

void bg(int job_number)
{
    struct bg *temp;
    temp = first;
    while (temp != NULL)
    {
        if (temp->job_number == job_number)
        {
            break;
        }
    }
    if (temp == NULL)
    {
        printf("This job number does not exist\n");
        return;
    }

    int pid = temp->pid;
    printf("%d\n", pid);
    signal(SIGCHLD, bg_exit);
    if (kill(pid, SIGCONT) != 0)
    {
        perror("Signal Error ");
        return;
    }
    // kill(pid, SIGCONT);
    // set the status to running
}