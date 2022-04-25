#include "headers.h"

void cd(char *arg)
{
    getcwd(temp_dir, 1000);
    if (strcmp(arg, "~") == 0)
    {

        if (chdir(home) == -1)
        {
            perror("Error");
        }
    }
    else if (strcmp(arg, "-") == 0)
    {
        getcwd(temp_dir, 1000);
        printf("%s\n", prev_dir);
        if (chdir(prev_dir) == -1)
        {
            perror("Error");
        }
    }
    else
    {
        if (chdir(arg) == -1)
        {
            perror("Error");
        }
    }

    strcpy(prev_dir, temp_dir);
}
