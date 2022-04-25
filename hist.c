#include "headers.h"

int count_lines()
{
    FILE *f;
    f = fopen(hist_string, "r");
    if (f == NULL)
    {
        return 0;
    }
    int count = 1;
    char c;
    while (1)
    {
        if (feof(f))
        {
            break;
        }
        c = fgetc(f);
        if (c == '\n')
        {
            count++;
        }
    }
    fclose(f);
    return count;
}

void insert_hist()
{

    FILE *f, *f1;
    int count = count_lines();
    f = fopen(hist_string, "r");
    if (f == NULL)
    {
        return;
    }
    char c;
    if (count > 21)
    {
        // printf("Entered");
        int line_count = 0;
        f1 = fopen(copy_string, "w");
        c = getc(f);
        // printf("c %c\n", c);
        while (!feof(f))
        {
            c = fgetc(f);
            if (line_count != 0)
            {
                fputc(c, f1);

                // printf("c - %c ", c);
            }
            if (c == '\n')
            {
                line_count++;
            }
            if (line_count == count - 1)
            {
                break;
            }
        }

        fclose(f1);
        remove(hist_string);
        rename(copy_string, hist_string);
    }
    fclose(f);
    // printf("Done");
}

void add_hist(char *line)
{
    FILE *f;
    f = fopen(hist_string, "a");
    fprintf(f, "%s\n", line);
    fclose(f);
    insert_hist();
    return;
}
