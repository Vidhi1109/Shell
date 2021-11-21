#include "headers.h"

void bg_cmd()
{
    if (arg_num != 2)
    {
        printf("Invalid number of arguments\n");
        return;
    }
    int job_number = atoi(args[1]);

    if (bgprocesses[job_number - 1] != -12)
    {
        if (kill(bgprocesses[job_number - 1], SIGCONT) < 0)
        {
            perror("");
            return;
        }
    }
    else
    {
        printf("Job number %d is invalid\n", job_number);
        return;
    }
}

void fg_cmd()
{
    if (arg_num != 2)
    {
        printf("Invalid number of arguments\n");
        return;
    }
    int job_number = atoi(args[1]);
    //printf("%d\n",bgprocesses[job_number-1]);
    if (bgprocesses[job_number - 1] != -12)
    {
        signal(SIGTTOU, SIG_IGN);
        signal(SIGTTIN, SIG_IGN);
        tcsetpgrp(0, getpgid(bgprocesses[job_number - 1]));
        if (kill(bgprocesses[job_number - 1], SIGCONT) < 0)
        {
            perror("");
        }
        int status;
        int pid = bgprocesses[job_number - 1];
        char str[strlen(bgpname[job_number - 1]) + 1];
        strcpy(str, bgpname[job_number - 1]);
        bgprocesses[job_number - 1] = -12;
        waitpid(pid, &status, WUNTRACED);
        tcsetpgrp(0, getpgid(pid_myshell));
        signal(SIGTTOU, SIG_DFL);
        signal(SIGTTIN, SIG_DFL);
        if (WIFSTOPPED(status))
        {
            bgprocesses[job_number-1]= pid;
            strcpy(bgpname[job_number-1],str);
        }
    }
    else
    {
        printf("Job number %d is invalid\n", job_number);
        return;
    }
}

// void fg_cmd()
// {
//     if (arg_num != 2)
//     {
//         printf("Invalid number of arguments\n");
//         return;
//     }
//     int job_number = atoi(args[1]);

//     if (bgprocesses[job_number - 1] != -12)
//     {
//         signal(SIGTTOU, SIG_IGN);
//         signal(SIGTTIN, SIG_IGN);
//         tcsetpgrp(0, getpgid(bgprocesses[job_number - 1]));
//         if (kill(bgprocesses[job_number - 1], SIGCONT) < 0)
//         {
//             perror("");
//         }
//         int status;
//         int pid = bgprocesses[job_number - 1];
//         char str[strlen(bgpname[job_number - 1]) + 1];
//         strcpy(str, bgpname[job_number - 1]);
//         bgprocesses[job_number - 1] = -12;
//         int pid = 
//         waitpid(bgprocesses[job_number - 1], &status, WUNTRACED);
//         tcsetpgrp(0, getpgid(pid_myshell));
//         signal(SIGTTOU, SIG_DFL);
//         signal(SIGTTIN, SIG_DFL);
//         if (WIFSTOPPED(status))
//         {
//             bgprocesses[job_number-1]=-12;
//             strcpy(bgpname[job_number-1],str);
//         }
//     }
//     else
//     {
//         printf("Job number %d is invalid\n", job_number);
//         return;
//     }
// }