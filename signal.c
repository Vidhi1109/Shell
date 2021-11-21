#include "headers.h"

void sig()
{
    if (arg_num != 3)
    {
        printf("Incorrect number of arguments\n");
    }
    int job_number = atoi(args[1]);
    int signal = atoi(args[2]);

    if (bgprocesses[job_number - 1] != -12)
    {
        flag = true;
        if (kill(bgprocesses[job_number - 1], signal) < 0)
        {
            perror("");
        }
    }
    else
    {
        printf("Job number %d is not valid\n", job_number);
    }
    return;
}