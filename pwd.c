#include "headers.h"

void my_pwd()
{
    char abspath[256] = "";
    getcwd(abspath, 256);
    printf("%s\n", abspath);
}