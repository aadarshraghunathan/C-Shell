#include "headers.h"

void print_path()
{
    char abspath[256] = "";
    getcwd(abspath, 256);
    char path[256];
    path[0] = '~';
    int len;
    len = strlen(home);
    char *buff;
    buff = strstr(abspath, home);
    //printf("%s\n", buff);
    if (buff != NULL)
    {
        int i;
        int k = 1;
        for (i = len; abspath[i] != '\0'; i++)
        {
            path[k] = abspath[i];
            k++;
        }
        path[k] = '\0';

        printf("%s: ", path);
    }
    else
    {

        printf("%s:", abspath);
    }
}
// int main()
// {
//     print_path();
//     return 0;
// }
