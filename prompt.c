#include "prompt.h"
#include "headers.h"
#include "print_path.h"

void prompt()
{
    char *buf;
    buf = (char *)malloc(100 * sizeof(char));
    buf = getlogin();
    printf("%s@", buf);
    struct utsname buffer;

    errno = 0;
    if (uname(&buffer) < 0)
    {
        perror("uname");
        exit(0);
    }
    printf("%s:", buffer.nodename);
    print_path();
}
