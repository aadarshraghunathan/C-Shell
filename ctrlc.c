#include "headers.h"

void ctrl_c_handler()
{
    // find foreground process
    if (fg_pid != -1)
    {
        kill(fg_pid, SIGINT);
    }

    return;
}