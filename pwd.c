#include "headers.h"

void pwd()
{
    char* c = getcwd(curr_dir,PATH_SIZE);
    if(c==NULL)
    {
        perror("pwd");
    }
    else
    {
        printf("%s\n",curr_dir);
    }
}