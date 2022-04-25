#include "headers.h"
#include "hist.h"

void history(int num)
{
    FILE *f;
    f = fopen(hist_string, "r");
    int count;
    count = count_lines();
    int start;
    char c;
    if (num > count)
    {
        start = 0;
    }
    else
    {
        start = count - num - 1;
    }
    c = getc(f);
    // printf("c %c\n", c);
    int line_count = 0;
    while (!feof(f))
    {

        if (line_count >= start)
        {
            printf("%c", c);
        }
        c = fgetc(f);
        if (c == '\n')
        {
            line_count++;
        }
        if (line_count == count - 1)
        {
            break;
        }
    }
    printf("\n");
}