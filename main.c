
#include "headers.h"

int main()
{
    // control + C
    signal(SIGTSTP, ctrl_z_handler);
    signal(SIGINT, ctrl_c_handler);
    fg_pid = -1;
    int input_default;
    int output_default;
    input_default = dup(STDIN_FILENO);
    output_default = dup(STDOUT_FILENO);
    first = NULL;
    getcwd(home, 1000);
    getcwd(prev_dir, 1000);
    getcwd(temp_dir, 1000);
    sprintf(hist_string, "%s/%s", home, "history.txt");
    sprintf(copy_string, "%s/%s", home, "copy.txt");
    job_num = 1;
quit:

    while (1)
    {
        // first = (struct bg *)malloc(sizeof(struct bg *));
        // first->next = NULL;
        // first = NULL;

        dup2(input_default, STDIN_FILENO);
        dup2(output_default, STDOUT_FILENO);
        prompt();
        int line_size;
        char *line;
        line = (char *)malloc(1000 * sizeof(char));
        char *command[100];
        for (int q = 0; q < 100; q++)
        {
            command[q] = (char *)calloc(1024, sizeof(char));
        }
        char *temp = (char *)malloc(100);
        int forkreturn;
        int bufsize = 32;
        // TAKE INPUT HERE
        line_size = getline(&line, &bufsize, stdin);
        if (line_size == (unsigned long)-1)
        {
            printf("\n");
            exit(0);
        }
        line[strlen(line) - 1] = '\0';
        int empty_line = 1;
        for (int g = 0; line[g] != '\0'; g++)
        {
            if (line[g] != ' ')
            {
                empty_line = 0;
            }
        }
        if (empty_line)
            continue;
        ;
        char buff[80];
        strcpy(buff, line);

        add_hist(line);
        // memcpy(&command, 0, 100);
        command[0] = strtok(buff, ";");
        int semicolon = 1;
        while (command[semicolon - 1] != NULL)
        {
            command[semicolon] = strtok(NULL, ";");
            semicolon++;
        }
        char *command1[100];
        // char *command2[100];
        for (int q = 0; q < 100; q++)
        {
            command1[q] = (char *)calloc(1024, sizeof(char));
            // command2[q] = (char *)calloc(1024, sizeof(char));
        }
        for (int t = 0; t < semicolon - 1; t++)
        {
            strcpy(command1[t], command[t]);
            // strcpy(command2[t], command[t]);
            // command[t] = '\0';
        }

        int sep_command = 0;
        while (sep_command != semicolon - 1)
        {
            dup2(input_default, STDIN_FILENO);
            dup2(output_default, STDOUT_FILENO);
            char *piped[100];
            for (int q = 0; q < 100; q++)
            {
                piped[q] = (char *)calloc(1024, sizeof(char));
            }
            int loc = 1;
            piped[0] = strtok(command[sep_command], "|");
            while (piped[loc - 1] != NULL)
            {
                piped[loc] = strtok(NULL, "|");
                loc++;
            }
            sep_command++;

            int piped_command = 0;
            int pip[2];
            if (loc > 2)
            {
                if (pipe(pip) < 0)
                {
                    printf("Could not create pipe\n");
                    goto quit;
                    ;
                }
            }
            while (piped_command != loc - 1)
            {

                // dup2(input_default, STDIN_FILENO);
                // dup2(output_default, STDOUT_FILENO);

                int inp_redirection = -1;
                int out_redirection1 = -1;
                int out_redirection2 = -1;
                if (loc > 2)
                {
                    if (piped_command == 0)
                    {
                        dup2(pip[1], STDOUT_FILENO);
                        close(pip[1]);
                    }
                    else if (piped_command > 0)
                    {
                        dup2(pip[1], STDOUT_FILENO);
                        dup2(pip[0], STDIN_FILENO);
                        close(pip[1]);
                        close(pip[0]);
                    }
                    if (piped_command == loc - 2)
                    {
                        dup2(output_default, STDOUT_FILENO);
                    }
                }

                int total;
                char *args[100];
                for (int q = 0; q < 100; q++)
                {
                    args[q] = (char *)calloc(1024, sizeof(char));
                }
                int count = 1;
                args[0] = strtok(piped[piped_command], "\n\t ");
                do
                {
                    args[count] = (char *)malloc(100 * sizeof(char));

                    args[count] = strtok(NULL, "\n\t ");
                    if (args[count] != NULL && strcmp(args[count], "<") == 0)
                    {
                        inp_redirection = count;
                        count--;
                    }
                    if (args[count] != NULL && strcmp(args[count], ">") == 0)
                    {
                        out_redirection1 = count;
                        count--;
                    }
                    if (args[count] != NULL && strcmp(args[count], ">>") == 0)
                    {
                        out_redirection2 = count;
                        count--;
                    }
                    count++;
                } while (args[count - 1] != NULL);
                total = count - 2;
                piped_command++;

                if (inp_redirection != -1)
                {
                    char inp_file[100];
                    if (args[inp_redirection] == NULL)
                    {

                        printf("%s\n", "Invalid input file");
                        goto quit;
                        ;
                    }
                    strcpy(inp_file, args[inp_redirection]);
                    for (int z = inp_redirection; z < total; z++)
                    {
                        strcpy(args[z], args[z + 1]);
                    }
                    args[total] = NULL;
                    total--;
                    if (out_redirection1 != -1)
                        out_redirection1--;
                    if (out_redirection2 != -1)
                        out_redirection2--;
                    count--;
                    if (access(inp_file, F_OK) != 0)
                    {
                        perror("Error");
                        goto quit;
                        ;
                    }
                    int fd = open(inp_file, O_RDONLY, 0);
                    dup2(fd, STDIN_FILENO);
                    close(fd);
                }
                if (out_redirection1 != -1)
                {
                    char out_file[100];
                    if (args[out_redirection1] == NULL)
                    {
                        printf("%s\n", "Invalid input file");
                        goto quit;
                        ;
                    }
                    strcpy(out_file, args[out_redirection1]);
                    for (int z = out_redirection1; z < total; z++)
                    {
                        strcpy(args[z], args[z + 1]);
                    }

                    args[total] = NULL;
                    total--;
                    if (out_redirection2 != -1)
                    {
                        out_redirection2--;
                    }

                    count--;
                    int fd1 = open(out_file, O_RDWR | O_TRUNC | O_CREAT, 0644);
                    dup2(fd1, STDOUT_FILENO);
                    close(fd1);
                }
                if (out_redirection2 != -1)
                {
                    char out_file[100];
                    if (args[out_redirection2] == NULL)
                    {
                        printf("%s\n", "Invalid input file");
                        goto quit;
                        ;
                    }
                    strcpy(out_file, args[out_redirection2]);
                    for (int z = out_redirection2; z < total; z++)
                    {
                        strcpy(args[z], args[z + 1]);
                    }
                    args[total] = NULL;
                    total--;
                    count--;
                    int fd1 = open(out_file, O_RDWR | O_APPEND | O_CREAT, 0644);
                    dup2(fd1, STDOUT_FILENO);
                    close(fd1);
                }
                int background = 0;
                if (strcmp(args[count - 2], "&") == 0)
                {
                    background = 1;
                    args[count - 2] = NULL;
                }

                if (strcmp(args[0], "ls") == 0)
                {

                    ls(args, count);
                }
                else if (strcmp(args[0], "jobs") == 0)
                {
                    jobs(args, count);
                }
                else if (strcmp(args[0], "pwd") == 0)
                {
                    my_pwd();
                }
                else if (strcmp(args[0], "fg") == 0)
                {
                    int jno;
                    if (count == 2)
                    {
                        printf("Invalid command \n");
                        goto quit;
                        ;
                    }
                    jno = atoi(args[1]);
                    fg(jno);
                }
                else if (strcmp(args[0], "bg") == 0)
                {
                    int jno;
                    if (count == 2)
                    {
                        printf("Invalid command\n");
                        goto quit;
                        ;
                    }
                    jno = atoi(args[1]);
                    bg(jno);
                }
                else if (strcmp(args[0], "sig") == 0)
                {
                    int jno, signo;
                    jno = atoi(args[1]);
                    signo = atoi(args[2]);
                    sig_function(jno, signo);
                }
                else if (strcmp(args[0], "cd") == 0)
                {
                    if (count == 2)
                    {
                        temp = "~";
                    }
                    else
                    {
                        temp = args[1];
                    }
                    cd(temp);
                }
                else if (strcmp(args[0], "pinfo") == 0)
                {
                    int val;
                    if (count == 2)
                    {
                        val = -1;
                    }
                    else
                    {
                        val = atoi(args[1]);
                        if ((getpgid(val) < 0))
                        {
                            // printf("process %d does not exist\n", val);
                            perror("Error :");
                            goto quit;
                            ;
                        }
                    }

                    pinfo(val);
                }
                else if (strcmp(args[0], "echo") == 0)
                {
                    echo(args);
                }
                else if (strcmp(args[0], "history") == 0)
                {
                    int val;
                    if (count == 2)
                    {
                        val = 10;
                    }
                    else
                    {
                        val = atoi(args[1]);
                    }
                    history(val);
                }
                else if (strcmp(args[0], "repeat") == 0)
                {
                    int forkreturn1;
                    forkreturn = fork();
                    if (forkreturn == 0)
                    {
                        setpgid(0, 0);
                        int gid = getpgid(0);
                        int i = 0;
                        int val;
                        val = atoi(args[1]);
                        while (i < val)
                        {
                            i++;
                            if (strcmp(args[2], "cd") == 0)
                            {

                                if (count == 4)
                                {
                                    temp = "~";
                                }
                                else
                                {
                                    temp = args[3];
                                }
                                cd(temp);
                            }
                            else if (strcmp(args[2], "ls") == 0)
                            {
                                ls(args + 2, count - 2);
                            }
                            else if (strcmp(args[2], "echo") == 0)
                            {
                                echo(args + 2);
                            }
                            else if (strcmp(args[2], "pwd") == 0)
                            {
                                my_pwd();
                            }
                            else if (strcmp(args[2], "pinfo") == 0)
                            {

                                int val;
                                if (count == 4)
                                {
                                    val = -1;
                                }
                                else
                                {
                                    val = atoi(args[3]);
                                    if ((getpgid(val) < 0))
                                    {
                                        // printf("process %d does not exist\n", val);
                                        perror("Error :");
                                        goto quit;
                                        ;
                                    }
                                }
                                pinfo(val);
                            }
                            else if (strcmp(args[2], "history") == 0)
                            {

                                int val;
                                if (count == 4)
                                {
                                    val = 10;
                                }
                                else
                                {
                                    val = atoi(args[3]);
                                }
                                history(val);
                            }
                            else
                            {
                                forkreturn1 = fork();
                                if (forkreturn1 < 0)
                                {
                                    perror("Error ");
                                    return 0;
                                }
                                if (forkreturn1 == 0)
                                {
                                    setpgid(0, gid);
                                    if (execvp(args[2], args + 2) < 0)
                                    {
                                        fprintf(stderr, "Command doesn't exist\n");
                                        goto quit;
                                        ;
                                    }
                                }
                                else
                                {
                                    int stat;
                                    waitpid(forkreturn1, &stat, WUNTRACED);
                                }
                            }
                        }
                    }
                    else
                    {
                        fg_pid = forkreturn;
                        int stat;
                        if (command1[sep_command - 1][strlen(command1[sep_command - 1]) - 1] == '&')
                        {
                            command1[sep_command - 1][strlen(command1[sep_command - 1]) - 1] = '\0';
                        }
                        strcpy(name, command1[sep_command - 1]);
                        signal(SIGTTOU, SIG_IGN);
                        signal(SIGTTIN, SIG_IGN);
                        tcsetpgrp(STDIN_FILENO, fg_pid);
                        waitpid(fg_pid, &stat, WUNTRACED);
                        tcsetpgrp(STDIN_FILENO, getpgrp());
                        signal(SIGTTOU, SIG_DFL);
                        signal(SIGTTIN, SIG_DFL);

                        if (WIFSTOPPED(stat))
                        {
                            insert_bg(fg_pid, name);
                        }
                        fg_pid = -1;
                    }
                }
                else
                {
                    if (!background)
                    {
                        forkreturn = fork();
                        if (forkreturn < 0)
                        {
                            perror("Error ");
                            return 0;
                        }
                        if (forkreturn == 0)
                        {
                            setpgid(0, 0);
                            if (execvp(args[0], args) < 0)
                            {

                                fprintf(stderr, "Command doesn't exist\n");
                                goto quit;
                                ;
                            }
                        }
                        else
                        {
                            fg_pid = forkreturn;
                            if (command1[sep_command - 1][strlen(command1[sep_command - 1]) - 1] == '&')
                            {
                                command1[sep_command - 1][strlen(command1[sep_command - 1]) - 1] = '\0';
                            }
                            strcpy(name, command1[sep_command - 1]);
                            int stat;

                            signal(SIGTTOU, SIG_IGN);
                            signal(SIGTTIN, SIG_IGN);
                            tcsetpgrp(STDIN_FILENO, fg_pid);
                            waitpid(fg_pid, &stat, WUNTRACED);
                            tcsetpgrp(STDIN_FILENO, getpgrp());
                            signal(SIGTTOU, SIG_DFL);
                            signal(SIGTTIN, SIG_DFL);

                            if (WIFSTOPPED(stat))
                            {
                                insert_bg(fg_pid, name);
                            }
                            fg_pid = -1;
                        }
                    }
                    else
                    {
                        forkreturn = fork();
                        if (forkreturn < 0)
                        {
                            perror("Error ");
                            return 0;
                        }
                        if (forkreturn == 0)
                        {
                            setpgid(0, 0);
                            if (execvp(args[0], args) < 0)
                            {
                                fprintf(stderr, "Command doesn't exist\n");
                                goto quit;
                            }
                        }
                        else
                        {
                            setpgid(forkreturn, 0);
                            // printf("%d\n", forkreturn);
                            // printf("%d\n", sep_command);
                            // printf("%s\n", command1[sep_command - 1]);
                            // if (command1[sep_command - 1][strlen(command1[sep_command - 1]) - 1] == '&')
                            // {
                            //     command1[sep_command - 1][strlen(command1[sep_command - 1]) - 1] = '\0';
                            // }
                            for (int b = 0; b < strlen(command1[sep_command - 1]); b++)
                            {
                                if (command1[sep_command - 1][b] == '&')
                                {
                                    command1[sep_command - 1][b] = '\0';
                                }
                            }
                            insert_bg(forkreturn, command1[sep_command - 1]);
                            signal(SIGCHLD, bg_exit);
                        }
                    }
                }
            }
        }
    }
}
