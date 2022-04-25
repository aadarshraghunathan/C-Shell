#include <stdio.h>
#include <dirent.h>
#include "ls.h"
#include "headers.h"

void l(char *filename, char *path)
{
    struct stat buf;

    stat(path, &buf);

    int size = buf.st_size;

    if (S_ISDIR(buf.st_mode))
    {
        printf("d");
    }
    else
    {

        printf("-");
    }
    if (buf.st_mode & S_IRUSR)
    {
        printf("r");
    }
    else
    {
        printf("-");
    }
    if (buf.st_mode & S_IWUSR)
    {
        printf("w");
    }
    else
    {
        printf("-");
    }
    if (buf.st_mode & S_IXUSR)
    {
        printf("x");
    }
    else
    {
        printf("-");
    }
    if (buf.st_mode & S_IRGRP)
    {
        printf("r");
    }
    else
    {
        printf("-");
    }
    if (buf.st_mode & S_IWGRP)
    {
        printf("w");
    }
    else
    {
        printf("-");
    }
    if (buf.st_mode & S_IXGRP)
    {
        printf("x");
    }
    else
    {
        printf("-");
    }
    if (buf.st_mode & S_IROTH)
    {
        printf("r");
    }
    else
    {
        printf("-");
    }
    if (buf.st_mode & S_IWOTH)
    {
        printf("w");
    }
    else
    {
        printf("-");
    }
    if (buf.st_mode & S_IXOTH)
    {
        printf("x");
    }
    else
    {
        printf("-");
    }
    printf(" ");
    int no_link = buf.st_nlink;
    printf("%d ", no_link);
    uid_t uid = buf.st_uid;
    gid_t gid = buf.st_gid;
    struct passwd *p;
    p = getpwuid(uid);
    if (p != NULL)
        printf("%s ", p->pw_name);
    struct group *g;
    g = getgrgid(gid);
    if (g != NULL)
        printf("%s ", g->gr_name);
    printf("%d ", size);
    struct tm *temp = localtime(&(buf.st_mtime));
    struct tm mod_time;
    mod_time.tm_year = temp->tm_year;
    mod_time.tm_mon = temp->tm_mon;
    mod_time.tm_mday = temp->tm_mday;
    char date[25];
    char year[25];
    strftime(date, 25, "%b %d %X", temp);
    strftime(year, 25, "%b %d %Y", temp);

    time_t now = time(0);
    struct tm *curr = localtime(&now);
    if (curr->tm_year != mod_time.tm_year)
    {
        printf("%s ", year);
    }
    else if (curr->tm_mon - mod_time.tm_mon > 6)
    {
        printf("%s ", year);
    }
    else if (curr->tm_mon - mod_time.tm_mon == 6)
    {
        if (curr->tm_mday >= mod_time.tm_mday)
        {
            printf("%s ", year);
        }
        else
        {
            printf("%s ", date);
        }
    }
    else
    {
        printf("%s ", date);
    }
    printf("%s\n", filename);
}

void ls(char **args, int count)
{

    //sleep(10);
    char *dir[100];
    for (int j = 0; j < 100; j++)
    {
        dir[j] = (char *)malloc(1024 * sizeof(char));
    }
    int count_dir = 0;
    int a_flag = 0;
    int l_flag = 0;

    int i = 1;

    int temp;
    temp = count;
    while (temp > 2)
    {
        if (args[i][0] == '-')
        {
            for (int k = 1; args[i][k] != '\0'; k++)
            {
                if (args[i][k] == 'a')
                {
                    a_flag = 1;
                }
                else if (args[i][k] == 'l')
                {
                    l_flag = 1;
                }
                else
                {
                    printf("Invalid flag\n");
                    return;
                }
            }
        }
        else
        {
            // dir[count_dir] = args[i];
            strcpy(dir[count_dir], args[i]);
            // printf("-----%s-------\n", dir[count_dir]);
            count_dir++;
        }
        i++;
        temp--;
    }

    if (count_dir == 0)
    {
        dir[0] = (char *)malloc(sizeof("."));
        dir[0] = ".";
        count_dir++;
    }

    for (i = 0; i < count_dir; i++)
    {
        // printf("------------%s-----------------", dir[i]);

        if (dir[i][0] == '~')
        {
            char buffer[1000];
            sprintf(buffer, "%s%s", home, dir[i] + 1);
            // memcpy(dir[i], buffer, sizeof(buffer));
            strcpy(dir[i], buffer);
        }

        struct stat buf;

        stat(dir[i], &buf);

        if (count_dir > 1)
        {

            if (S_ISDIR(buf.st_mode))
            {
                printf("%s:\n", dir[i]);
            }
        }

        // Check if it is a file

        if (S_ISREG(buf.st_mode))
        {
            if (l_flag)
            {
                l(dir[i], dir[i]);
            }
            else
            {
                printf("%s\n", dir[i]);
            }
            continue;
        }

        DIR *dirp;
        // printf("**%s**", dir[i]);
        dirp = opendir(dir[i]);
        struct dirent *d;
        if (dirp == NULL)
        // printf("%d\n", buf.st_mode);
        {
            // if (!(buf.st_mode & S_IRUSR))
            // {
            //     printf("The directory cannot be read , Permission denied\n");
            // }
            // else
            // {
            //     printf("No such directory or file\n");
            // }
            // continue;
            perror("Error ");
            continue;
        }

        if (l_flag)
        {
            printf("total %ld\n", buf.st_blocks);
        }
        while (1)
        {
            d = readdir(dirp);
            if (d == NULL)
            {
                break;
            }
            else
            {
                //     printf("Name %s\n", d->d_name);

                char full[1000];
                sprintf(full, "%s/%s", dir[i], d->d_name);
                if (a_flag && l_flag)
                {

                    l(d->d_name, full);
                }
                else if (l_flag)
                {
                    if (d->d_name[0] != '.')
                    {

                        l(d->d_name, full);
                    }
                }
                else if (a_flag)
                {

                    printf("%s\n", d->d_name);
                }
                else
                {
                    if (d->d_name[0] != '.')
                    {
                        printf("%s\n", d->d_name);
                    }
                }
            }
        }
        closedir(dirp);
    }
}
