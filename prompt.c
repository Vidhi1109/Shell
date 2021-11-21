#include "headers.h"

void prompt(int invoke)
{
    char system_name[NAME_SIZE];
    char dir_path[PATH_SIZE];
    struct passwd* name = getpwuid(getuid());
    gethostname(system_name,NAME_SIZE);
    getcwd(dir_path,PATH_SIZE);   
    if(invoke==0)
    {
        getcwd(home_dir,PATH_SIZE);
        getcwd(prev_dir,PATH_SIZE);
        printf("<%s@%s:%s>",name->pw_name,system_name,"~");
    }
    else
    {
        getcwd(dir_path,PATH_SIZE);
        if(strncmp(dir_path,home_dir,strlen(home_dir))==0)
        {
            printf("<%s@%s:~%s>",name->pw_name,system_name,&dir_path[strlen(home_dir)]);
        }
        else
        {
            printf("<%s@%s:%s>",name->pw_name,system_name,dir_path);
        }
    }
}