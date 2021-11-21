#include "headers.h"
void bg(char *process_name, char **args, bool flag)
{
    pid_t shell = getpid();
    int j = 0;
    for (int i = 0; i < arg_num; i++)
    {
        if (strcmp(args[i], "&") != 0)
        {
            args[j++] = args[i];
        }
    }
    args[j] = '\0';
    pid_t child = fork();

    if (child == -1)
    {
        perror("Forking failed");
    }
    else if (child == 0 && flag == true)
    {
        setpgid(0, 0);
        //close(STDERR_FILENO);
        //printf("comeshere\n");
        if (execvp(args[0], args) < 0)
        {
            char message[PATH_SIZE];
            sprintf(message, "Command %s cannot be executed", args[0]);
            perror(message);
            exit(1);
        }
        exit(0);
    }
    else if (child == 0 && flag == false)
    {
        if (execvp(args[0], args) < 0)
        {
            char message[PATH_SIZE];
            sprintf(message, "Command %s cannot be executed", args[0]);
            perror(message);
            exit(1);
        }
        exit(0);
    }
    else if (child > 0 && flag == true)
    {
        dup2(reserve_inp_file, STDIN_FILENO);
        dup2(reserve_output_file, STDOUT_FILENO);
        printf("%d\n", child);
        bg_cnt = bg_cnt % 10000;
        bgprocesses[bg_cnt++] = child;
        strcpy(bgpname[bg_cnt-1] , args[0]);
        for (int i = 1; i < arg_num; i++)
        {
            if (args[i] != NULL)
            {
                if (strlen(bgpname[bg_cnt - 1]) + strlen(args[i]) < 2000)
                {
                    strcat(bgpname[bg_cnt - 1] , " ");
                    strcat(bgpname[bg_cnt - 1], args[i]);
                }
            }
        }
    }
    else if (child > 0 && flag == false)
    {
        process_id = child;
        dup2(reserve_inp_file, STDIN_FILENO);
        dup2(reserve_output_file, STDOUT_FILENO);
        int status;
        waitpid(child, &status, WUNTRACED);
        if (WIFSTOPPED(status))
        {
            bgprocesses[bg_cnt++] = child;
            strcpy(bgpname[bg_cnt-1] , args[0]);
            for (int i = 1; i < arg_num; i++)
            {
                if (strlen(bgpname[bg_cnt - 1]) + strlen(args[i]) < 2000)
                {
                    strcat(bgpname[bg_cnt - 1] , " ");
                    strcat(bgpname[bg_cnt - 1], args[i]);
                }
            }
        }
    }
}