#ifndef __ECHO_H
#define __ECHO_H

void bg_exit();

struct bg
{
    struct bg *next;
    char *name;
    int pid;
    int job_number;
};

#endif
