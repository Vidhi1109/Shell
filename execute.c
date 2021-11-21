#include "headers.h"
bool check()
{
    int loop = arg_num;
    for (int i = 0; i < loop; i++)
    {
        if (args[i] != NULL && strcmp(args[i], ">") == 0)
        {

            if (right == true)
            {
                printf("Invalid synatx\n");
                return false;
            }
            if (i == 0 || i == arg_num - 1)
            {
                printf("Invalid Command\n");
                return false;
            }
            else
            {
                right = true;
                out_file = open(args[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
                if (out_file < 0)
                {
                    perror("Error opening file");
                    return false;
                }
                else
                {
                    dup2(out_file, STDOUT_FILENO);
                    close(out_file);
                }
                args[i] = '\0';
                args[i + 1] = '\0';
                arg_num = arg_num - 2;
            }
        }

        if (args[i] != NULL && strcmp(args[i], "<") == 0)
        {
            if (left == true)
            {
                printf("Invalid synatx\n");
                return false;
            }
            if (i == 0 || i == arg_num - 1)
            {
                printf("Invalid Command\n");
                return false;
            }
            else
            {
                left = true;
                in_file = open(args[i + 1], O_RDONLY, 0644);
                if (in_file < 0)
                {
                    perror("Error opening file");
                    return false;
                }
                else
                {
                    dup2(in_file, STDIN_FILENO);
                    close(in_file);
                }
                args[i] = '\0';
                args[i + 1] = '\0';
                arg_num = arg_num - 2;
            }
        }
        if (args[i] != NULL && strcmp(args[i], ">>") == 0)
        {
            if (dright == true)
            {
                return false;
            }
            if (i == 0 || i == arg_num - 1)
            {
                printf("Invalid Command\n");
                return false;
            }
            else
            {
                dright = true;
                dup2(out_file, STDOUT_FILENO);
                out_file = open(args[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
                if (out_file < 0)
                {
                    perror("Error opening file");
                    return false;
                }
                else
                {
                    dup2(out_file, STDOUT_FILENO);
                    close(out_file);
                }
                args[i] = '\0';
                args[i + 1] = '\0';
                arg_num = arg_num - 2;
            }
        }
    }
    return true;
}
void call()
{
    int std_in = dup(STDIN_FILENO);
    left = false, right = false, dright = false;
    bool var_check = check();
    if (var_check == false)
    {
        return;
    }
    if (strcmp(args[arg_num - 1], "&") == 0)
    {
        bg(args[0], args, flag);
        flag = false;
    }
    else if (strcmp(args[0], "cd") == 0)
    {
        cd();
        pdir_set = 1;
    }
    else if (strcmp(args[0], "echo") == 0)
        echo();
    else if (strcmp(args[0], "exit") == 0)
    {
        storeList();
        DeleteList(&L);
        exit(0);
    }
    else if (strcmp(args[0], "ls") == 0)
    {
        ls();
    }
    else if (strcmp(args[0], "pwd") == 0)
    {
        pwd();
    }
    else if (strcmp(args[0], "history") == 0)
    {
        history();
    }
    else if (strcmp(args[0], "pinfo") == 0)
    {
        pinfo();
    }
    else if (strcmp(args[0], "repeat") == 0)
    {
        repeat();
    }
    else if (strcmp(args[0], "jobs") == 0)
    {
        jobs();
    }
    else if (strcmp(args[0], "sig") == 0)
    {
        sig();
    }
    else if (strcmp(args[0], "fg") == 0)
    {
        fg_cmd();
    }
    else if (strcmp(args[0], "bg") == 0)
    {
        bg_cmd();
    }
    else
    {
        bg(args[0], args, flag);
    }
    if (left == true)
    {
        dup2(std_in, STDIN_FILENO);
    }
    // dup2(std_in , STDOUT_FILENO);
    // dup2(std_out , STDOUT_FILENO);
    dup2(reserve_inp_file, STDIN_FILENO);
    dup2(reserve_output_file, STDOUT_FILENO);
}

void execute(char *cmd)
{
    flag = false;
    char str[strlen(cmd) + 1];
    strcpy(str, cmd);
    arg_num = 0;
    char *c = strtok(str, " \t\n\v");
    if (c != NULL)
    {
        args[arg_num++] = c;
        if (strcmp(c, "&") == 0)
            flag = true;
    }
    while (c != NULL)
    {
        c = strtok(NULL, " \t\v\n");
        if (c != NULL)
        {
            args[arg_num++] = c;
            if (strcmp(c, "&") == 0)
                flag = true;
        }
    }
    args[arg_num] = NULL;
    call();
}