#include "headers.h"

void sig_function(int job_number, int sig_num)
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

    int pid;
    pid = temp->pid;
    kill(pid, sig_num);
}