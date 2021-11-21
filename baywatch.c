#include "headers.h"
#include <stdio.h>
void print_int(int col)
{
    FILE *fp = fopen("/proc/interrupts", "r");
    if (fp == NULL)
    {
        printf("File cannot be read\n");
        return;
    }
    else
    {
        char *line_buf = NULL;
        size_t line_buf_size = 0;
        int line_count = 0;
        ssize_t line_size;
        line_size = getline(&line_buf, &line_buf_size, fp);
        int i = 0;
        while (line_size >= 0)
        {
            if (line_count == 2)
            {
                char *c = strtok(line_buf, " \t\v");
                while (c != NULL)
                {
                    c = strtok(NULL, " \t\v");
                    if (c != NULL)
                    {
                        printf("%s ", c);
                        i++;
                    }
                    if (i == col)
                    {
                        break;
                    }
                }
                break;
            }
            line_size = getline(&line_buf, &line_buf_size, fp);
            line_count++;
        }
    }
    fclose(fp);
}

void baywatch()
{
    int n;
    if (arg_num != 4)
    {
        printf("Invalid number of arguments\n");
        return;
    }
    for (int i = 1; i < arg_num; i++)
    {
        if (strcmp(args[i], "-n") == 0)
        {
            if (args[i + 1] != NULL)
                n = atoi(args[i + 1]);
            else
            {
                printf("Invalid Command\n");
                return;
            }
            i++;
        }
        else if (strcmp(args[i], "interrupt") != 0)
        {
            printf("Invalid Command\n");
            return;
        }
    }
    char c;
    int col = 0;
    bool sig = false;
    clock_t time = clock();
    FILE *fp = fopen("/proc/interrupts", "r");
    if (fp == NULL)
    {
        printf("File cannot be read\n");
        return;
    }
    else
    {
        char *line_buf = NULL;
        size_t line_buf_size = 0;
        int line_count = 0;
        ssize_t line_size;
        line_size = getline(&line_buf, &line_buf_size, fp);
        char *state = strtok(line_buf, " \t\v");
        printf("%s", state);
        col++;
        while (state != NULL)
        {
            state = strtok(NULL, " \t\v");
            if (state != NULL)
            {
                printf(" %s", state);
                col++;
            }
        }
        int i = 0;
        clock_t init_time;
        while (1)
        {
            if (i == 0)
            {
                init_time = clock();
                print_int(col);
                init_time += n;
            }
            else if (init_time == clock())
            {
                //print_int(col);
            }
        }
        fclose(fp);
    }
}
char get_key()
{
    struct termios state;
    tcgetattr(0, &state);
    state.c_lflag &= ~(ICANON | ECHO); 
    tcsetattr(0, TCSANOW, &state);
    int buffer_count;
    ioctl(0, FIONREAD, &buffer_count);
    tcgetattr(0, &state);
    state.c_lflag |= ICANON | ECHO;
    tcsetattr(0, TCSANOW, &state);
    return (buffer_count == 0) ? '\0' : getchar();
}