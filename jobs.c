#include "headers.h"
#include "bg_exit.h"
#include "jobs.h"

void alphabetical_sort()
{

    struct bg *temp;
    temp = first;

    // while (temp != NULL)
    // {
    //     printf("%s\n", temp->name);
    //     temp = temp->next;
    // }
    int count = 0;
    struct bg *prev, *curr, *next;
    temp = first;
    while (temp != NULL)
    {
        temp = temp->next;
        count++;
    }
    // printf("%d\n", count);
    int i;
    for (i = 0; i < count; i++)
    {
        // printf(" First %s\n ", first->name);
        curr = first;
        prev = first;
        while (curr->next != NULL)
        {
            next = curr->next;
            if (curr == first)
            {

                if (strcmp(curr->name, next->name) > 0)
                {
                    curr->next = next->next;
                    next->next = curr;
                    first = next;
                    prev = next;
                }
                else
                {
                    curr = curr->next;
                    prev = first;
                }
            }
            else
            {
                // break;
                if (strcmp(curr->name, next->name) > 0)

                {
                    curr->next = next->next;
                    next->next = curr;
                    prev->next = next;
                    prev = next;
                }
                else
                {
                    curr = curr->next;
                    prev = prev->next;
                }
            }
        }
    }
}

char *get_status(int pid)
{
    char path[1024];
    sprintf(path, "/proc/%d/stat", pid);
    FILE *fp = fopen(path, "r");
    char proc[52][1000];
    fscanf(fp, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s", proc[0], proc[1], proc[2], proc[3], proc[4], proc[5], proc[6], proc[7], proc[8], proc[9], proc[10], proc[11], proc[12], proc[13], proc[14], proc[15], proc[16], proc[17], proc[18], proc[19], proc[20], proc[21], proc[22], proc[23], proc[24], proc[25], proc[26], proc[27], proc[28], proc[29], proc[30], proc[31], proc[32], proc[33], proc[34], proc[35], proc[36], proc[37], proc[38], proc[39], proc[40], proc[41], proc[42], proc[43], proc[44], proc[45], proc[46], proc[47], proc[48], proc[49], proc[50], proc[51]);
    // printf("%s\n", proc[2]);
    char *string;
    string = (char *)malloc(100 * sizeof(char));
    strcpy(string, proc[2]);
    return string;
}

void jobs(char **args, int count)
{
    int run = 0;
    int stop = 0;
    struct bg *temp;
    char *status;
    status = (char *)malloc(10 * sizeof(char));
    if (count != 2)
    {
        if (strcmp(args[1], "-r") == 0)
        {
            run = 1;
        }
        else if (strcmp(args[1], "-s") == 0)
        {
            stop = 1;
        }
    }
    alphabetical_sort();
    temp = first;
    if (run == 1)
    {
        while (temp != NULL)
        {
            int pid = temp->pid;
            status = get_status(pid);
            if (strcmp(status, "T") == 0)
            {
                temp = temp->next;
                continue;
            }
            printf("[%d] ", temp->job_number);
            printf(" Running");
            printf(" %s ", temp->name);
            printf(" [%d]\n", temp->pid);
            temp = temp->next;
        }
    }
    else if (stop == 1)
    {
        while (temp != NULL)
        {
            int pid = temp->pid;
            status = get_status(pid);
            if (strcmp(status, "T") != 0)
            {
                temp = temp->next;
                continue;
            }
            printf("[%d] ", temp->job_number);
            printf(" Stopped");
            printf(" %s ", temp->name);
            printf(" [%d]\n", temp->pid);
            temp = temp->next;
        }
    }
    else
    {
        while (temp != NULL)
        {
            int pid = temp->pid;
            status = get_status(pid);
            printf("[%d] ", temp->job_number);
            if (strcmp(status, "T") != 0)
            {
                printf(" Running");
            }
            else
            {
                printf(" Stopped");
            }
            printf(" %s ", temp->name);
            printf(" [%d]\n", temp->pid);
            temp = temp->next;
        }
    }
}
