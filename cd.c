#include "headers.h"
void cd()
{
    if (arg_num == 1)
    {
        char temporary[PATH_SIZE];
        getcwd(temporary, PATH_SIZE);
        if (chdir(home_dir) < 0)
        {
            perror("cd");
        }
        else
        {
            strcpy(prev_dir, temporary);
        }
    }
    else if (arg_num == 2)
    {
        char temporary[PATH_SIZE];
        getcwd(temporary, PATH_SIZE);
        if (strcmp(args[1], "~") == 0)
        {
            if (chdir(home_dir) < 0)
            {
                perror("cd");
            }
            else
            {
                strcpy(prev_dir, temporary);
            }
        }
        else if (strcmp(args[1], "-") == 0)
        {
            if (strcmp(prev_dir, "NULL") == 0 || pdir_set == 0)
            {
                printf("cd: OLDPWD not set\n");
            }
            else if (chdir(prev_dir) < 0)
            {
                perror("cd");
            }
            else
            {
                printf("%s\n", prev_dir);
                strcpy(prev_dir, temporary);
            }
        }
        else if (args[1][0] == '~')
        {
            char path[PATH_SIZE+1];
            sprintf(path, "%s/%s", home_dir, &args[1][2]);
            if (chdir(path) < 0)
            {
                perror("cd");
            }
            else
            {
                strcpy(prev_dir, temporary);
            }
        }
        else
        {
            if (chdir(args[1]) < 0)
            {
                perror("cd");
            }
            else
            {
                strcpy(prev_dir, temporary);
            }
        }
    }
    else
    {
        printf("cd: too many arguments\n");
    }
}