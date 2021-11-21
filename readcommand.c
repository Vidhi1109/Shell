#include "headers.h"
#include "linked.h"
void read_command()
{
    cmd_cnt = 0;
    char *read = (char *)malloc(sizeof(char) * 1000);
    size_t block_size = 0;
    int sign = getline(&read, &block_size, stdin);
    if (sign == -1)
    {
        printf("\n");
        storeList();
        DeleteList(&L);
        exit(0);
    }
    if (sign < 0)
    {
        return;
    }
    else if (read[0] == '\0' || read[0] == '\n')
    {
        return;
    }
    read[sign - 1] = '\0';
    InsertAtFront(&L, read);
    hist_cnt++;
    char *t = strtok(read, ";");
    if (t == NULL)
    {
        cmds[cmd_cnt++] = read;
    }
    else
    {
        cmds[cmd_cnt++] = t;
    }
    while (t != NULL)
    {
        t = strtok(NULL, ";");
        if (t != NULL)
        {
            cmds[cmd_cnt++] = t;
        }
    }

    for (int i = 0; i <= cmd_cnt - 1; i++)
    {
        int pipe_cnt = 0;
        if (strstr(cmds[i], "|") != NULL)
        {
            for (int j = 0; j < strlen(cmds[i]); j++)
            {
                if ((j == 0 && cmds[i][j] == '|') || (j == strlen(cmds[i]) - 1 && cmds[i][j] == '|') || (j != strlen(cmds[i]) - 1 && cmds[i][j] == '|' && cmds[i][j + 1] == '|'))
                {
                    printf("Invalid Syntax\n");
                }
            }
            char *token = strtok(cmds[i], "|");
            pipe_cmds[pipe_cnt++] = token;
            while (token != NULL)
            {
                token = strtok(NULL, "|");
                pipe_cmds[pipe_cnt++] = token;
            }
            int fds[2];
            int prev_fds[2];
            //printf("\n%d\n",pipe_cnt);

            for (int i = 0; i < pipe_cnt - 2; i++)
            {
                if (pipe(fds) < 0)
                {
                    perror("");
                }
                if (i == 0)
                {
                    int out = dup(STDOUT_FILENO);
                    dup2(fds[1], STDOUT_FILENO);
                    execute(pipe_cmds[i]);
                    close(fds[1]);
                    dup2(out, STDIN_FILENO);
                    close(out);
                }
                if (i > 0)
                {
                    int in = dup(STDIN_FILENO);
                    int out = dup(STDOUT_FILENO);
                    dup2(prev_fds[0], STDIN_FILENO);
                    dup2(fds[1], STDOUT_FILENO);
                    execute(pipe_cmds[i]);
                    close(prev_fds[0]);
                    close(fds[1]);
                    dup2(in, STDIN_FILENO);
                    dup2(out, STDIN_FILENO);
                    close(in);
                    close(out);
                }
                prev_fds[0] = fds[0];
                prev_fds[1] = fds[1];
            }
            dup2(reserve_output_file, STDOUT_FILENO);
            int in = dup(STDIN_FILENO);
            dup2(fds[0], STDIN_FILENO);
            execute(pipe_cmds[pipe_cnt - 2]);
            close(fds[0]);
            dup2(in, STDIN_FILENO);
            dup2(reserve_output_file, STDOUT_FILENO);
            close(in);
        }
        else
        {
            execute(cmds[i]);
        }
    }
}