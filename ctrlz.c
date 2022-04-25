#include "headers.h"

void ctrl_z_handler()
{

  
    if (fg_pid == -1)
    {
        return;
    }
    kill(fg_pid, SIGTSTP);
    insert_bg(fg_pid, name);
    fg_pid = -1;

    return;
}