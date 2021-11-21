#include "headers.h"
void pinfo()
{
    pid_t pid;
    char s1[PATH_SIZE];
    if (args[1] == NULL)
    {
        sprintf(s1, "/proc/self/stat");
    }
    else
    {
        sprintf(s1, "/proc/%s/stat", args[1]);
    }

    FILE *file_read = fopen(s1, "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char pstatus[PATH_SIZE];
    char read_str[PATH_SIZE];

    char pgrp[12], tpgid[12], state[5], c = '-';
    if (file_read == NULL)
    {
        printf("File %s can't be read\n", s1);
        return;
    }
    else
    {
        int count = 0;
        int ret = fscanf(file_read, "%s", read_str);
        while (ret == 1)
        {
            if (count == 2)
            {
                strcpy(state, read_str);
            }
            if (count == 4)
            {
                //printf("%s--pgrp\n", read_str);
                strcpy(pgrp, read_str);
            }
            if (count == 7)
            {
                //printf("%s--tpgid\n", read_str);
                strcpy(tpgid, read_str);
            }
            if (count == 0)
            {
                printf("pid--%s\n", read_str);
            }
            if (count == 2)
            {
                strcpy(pstatus, read_str);
            }
            if (count == 22)
            {
                if (strcmp(pgrp, tpgid) == 0)
                {
                    c = '+';
                }
                printf("Process Status -- {%s%c}\nmemory -- %s {Virtual Memory}\n", pstatus, c, read_str);
            }
            ret = fscanf(file_read, "%s", read_str);
            count++;
        }
    }
    char exec_path[PATH_SIZE];
    fclose(file_read);
    if (args[1] == NULL)
    {
        sprintf(s1, "/proc/self/exe");
    }
    else
    {
        sprintf(s1, "/proc/%s/exe", args[1]);
    }
    ssize_t ret = readlink(s1, exec_path, PATH_SIZE);
    exec_path[ret]='\0';
    if (ret < 0)
    {
        printf("File %s can't be read", s1);
        perror(" ");
        return;
    }
    char *p;
    //printf("EXEC_PATH-%s\n", exec_path);
    p = &exec_path[0];
    if (strncmp(exec_path, home_dir, strlen(home_dir)) == 0)
    {
        exec_path[strlen(home_dir) - 1] = '~';
        p = &exec_path[strlen(home_dir) - 1];
    }
    else
    {
        p = &exec_path[0];
    }
    printf("Executable Path -- %s\n", p);
}
