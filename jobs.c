#include "headers.h"

int cstring_cmp(const void *a, const void *b)
{
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    if (*ia == NULL && *ib == NULL)
        return 1;
    if (*ia == NULL)
        return 1;
    if (*ib == NULL)
        return 1;
    return strcmp(a, b);
}

void jobs()
{
    bool flagr = false, flags = false;
    for (int i = 1; i < arg_num; i++)
    {
        if (strcmp(args[i], "-r") == 0)
        {
            flagr = true;
        }
        else if (strcmp(args[i], "-s") == 0)
        {
            flags = true;
        }
        else
        {
            if (args[i] != NULL)
            {
                printf("Invalid argument: %s no such job\n", args[i]);
                return;
            }
        }
    }
    if (flagr == true && flags == true)
    {
        return;
    }
    int job_ids[bg_cnt];
    int job_pids[bg_cnt];
    char job_names[bg_cnt][1000];
    char path[PATH_SIZE];
    char tempo[1000];
    for (int i = 0; i < bg_cnt; i++)
    {
        job_ids[i]=i+1;
        job_pids[i] = bgprocesses[i];
        strcpy(job_names[i],bgpname[i]);
    }
    for (int i = 0; i < bg_cnt - 1; i++)
    {
        for (int j = i + 1; j < bg_cnt; j++)
        {
            if (strcmp(bgpname[i], bgpname[j]) > 0)
            {
                strcpy(tempo, job_names[i]);
                strcpy(job_names[i], job_names[j]);
                strcpy(job_names[j], tempo);
                int temp = job_ids[i];
                job_ids[i]=job_ids[j];
                job_ids[j]=temp;
                temp = job_pids[i];
                job_pids[i] = job_pids[j];
                job_pids[j]=temp;
            }
        }
    }

    for (int i = 0; i < bg_cnt; i++)
    {
        if (job_pids[i] != -12)
        {
            sprintf(path, "/proc/%d/status", job_pids[i]);
            FILE *fp = fopen(path, "r");
            if (fp == NULL)
            {
                printf("File %s can't be read\n", path);
                continue;
            }
            char *line_buf = NULL;
            size_t line_buf_size = 0;
            int line_count = 0;
            ssize_t line_size;
            line_size = getline(&line_buf, &line_buf_size, fp);
            while (line_size >= 0)
            {
                //printf("%d",line_count);
                if (line_count == 2)
                {
                    char *state = strtok(line_buf, " \t\v");
                    state = strtok(NULL, " \t\v");

                    if (strcmp(state, "R") == 0 || strcmp(state, "S") == 0 || strcmp(state, "D") == 0)
                    {
                        if ((flagr == false && flags == false) || (flagr == true))
                        {
                            printf("[%d] Running %s [%d]\n", job_ids[i], job_names[i], job_pids[i]);
                        }

                        break;
                    }
                    if ((flagr == false && flags == false) || (flags == true))
                    {
                        printf("[%d] Stopped %s [%d]\n", job_ids[i], job_names[i], job_pids[i]);
                    }
                    break;
                }

                line_count++;
                line_size = getline(&line_buf, &line_buf_size, fp);
            }
        }
    }
    // for (int i = 0; i < bg_cnt; i++)
    // {
    //     if (bgprocesses[i] != -12)
    //     {
    //         sprintf(path, "/proc/%d/status", bgprocesses[i]);
    //         FILE *fp = fopen(path, "r");
    //         if (fp == NULL)
    //         {
    //             printf("File %s can't be read\n", path);
    //             continue;
    //         }
    //         char *line_buf = NULL;
    //         size_t line_buf_size = 0;
    //         int line_count = 0;
    //         ssize_t line_size;
    //         line_size = getline(&line_buf, &line_buf_size, fp);
    //         while (line_size >= 0)
    //         {
    //             //printf("%d",line_count);
    //             if (line_count == 2)
    //             {
    //                 char *state = strtok(line_buf, " \t\v");
    //                 state = strtok(NULL, " \t\v");

    //                 if (strcmp(state, "R") == 0 || strcmp(state, "S") == 0 || strcmp(state, "D") == 0)
    //                 {
    //                     if ((flagr == false && flags == false) || (flagr == true))
    //                     {
    //                         printf("[%d] Running %s [%d]\n", i + 1, bgpname[i], bgprocesses[i]);
    //                     }

    //                     break;
    //                 }
    //                 if ((flagr == false && flags == false) || (flags == true))
    //                 {
    //                     printf("[%d] Stopped %s [%d]\n", i + 1, bgpname[i], bgprocesses[i]);
    //                 }
    //                 break;
    //             }

    //             line_count++;
    //             line_size = getline(&line_buf, &line_buf_size, fp);
    //         }
    //     }
    // }
}