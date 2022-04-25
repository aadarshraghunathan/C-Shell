#include "headers.h"
#include "prompt.h"

void print()
{
    // printf("Starting print\n");
    struct bg *temp;
    temp = first;
    while (temp != NULL)
    {
        printf("%d ", temp->pid);
        printf("%s \n", temp->name);
        temp = temp->next;
    }
    // printf("Ending print\n");
}
void insert_bg(int pid, char *name)
{
    // printf("Insert %s %d\n", name, pid);
    struct bg *new_node;
    new_node = (struct bg *)malloc(sizeof(struct bg *));
    new_node->name = (char *)malloc(sizeof(name) + 1);
    struct bg *temp;

    new_node->pid = pid;
    new_node->job_number = job_num;
    job_num++;
    strcpy(new_node->name, name);
    new_node->next = NULL;
    // printf("%s ", name);
    if (first == NULL)
    {
        first = new_node;
    }
    else
    {
        temp = first;
        int no_insert = -1;
        while (temp->next != NULL)
        {
            if (temp->job_number == new_node->job_number)
            {
                no_insert = 1;
            }
            temp = temp->next;
        }
        if (no_insert == -1)
        {
            temp->next = new_node;
        }
    }

    // printf("--------------------------\n");
    // print();
}

void delete (int pid)
{
    struct bg *temp;
    struct bg *prev;
    temp = first;
    prev = NULL;
    if (first->pid == pid)
    {
        first = first->next;
        return;
    }
    temp = first->next;
    prev = first;
    while (temp != NULL)
    {
        if (temp->pid == pid)
        {
            prev->next = temp->next;
            return;
        }
        temp = temp->next;
        prev = prev->next;
    }
}

char *search(int pid)
{
    struct bg *temp;
    temp = first;
    // printf("First %s ", first->name);
    while (temp != NULL)
    {
        if (temp->pid == pid)
        {
            return temp->name;
        }
        temp = temp->next;
    }
}

void bg_exit()
{
    pid_t pid;
    int status;
    char *name = "";
    while ((pid = waitpid((pid_t)(-1), &status, WNOHANG)) > 0)
    {

        name = search(pid);
        delete (pid);
        fprintf(stderr, "%s with pid %d exited with status %d\n", name, pid, WEXITSTATUS(status));
        return;
    }
}
