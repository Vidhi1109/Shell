#include "headers.h"
bool pro = false;
int invoke = 0;
void child_check(int signal)
{
    int status;
    pid_t pid = waitpid(-1, &status, WNOHANG);
    if (pid > 0)
    {
        for (int i = 0; i < 10000; i++)
        {
            if (bgprocesses[i] == pid)
            {
                if (status != 0)
                {
                    printf("\n%s with pid %d exited abnormally\n", bgpname[i], pid);
                    bgprocesses[i] = -12;
                    prompt(invoke);
                    fflush(stdout);
                    break;
                }
                else
                {
                    printf("\n%s with pid %d exited normally\n", bgpname[i], pid);
                    bgprocesses[i] = -12;
                    prompt(invoke);
                    fflush(stdout);
                    break;
                }
            }
        }
    }
}
void bg_check()
{
    for (int i = 0; i < 10000; i++)
    {
        int status;
        int k = waitpid(bgprocesses[i], &status, WNOHANG);
        if (bgprocesses[i] != 0 && (k == bgprocesses[i] || k == -1))
        {
            if (k == bgprocesses[i] && status == 0)
            {
                printf("%s with pid %d exited normally\n", bgpname[i], bgprocesses[i]);
                bgprocesses[i] = 0;
                //prompt(invoke);
                //fflush(stdout);
            }
            else
            {
                printf("%s with pid %d exited normally\n", bgpname[i], bgprocesses[i]);
                bgprocesses[i] = 0;
            }
        }
    }
}
void ctrlz()
{
    if (flag != true || strcmp(args[0], "fg") != 0)
    {
        printf("\r");
    }
}
void ctrl()
{
    if (process_id == -1 || process_id == pid_myshell)
    {
        printf("\n");
        prompt(invoke);
        fflush(stdout);
    }
}
int main(void)
{
    process_id = -1;
    int reserve_inp_file = dup(STDIN_FILENO);
    int reserve_output_file = dup(STDOUT_FILENO);
    pid_myshell = getpid();
    for (int i = 0; i < 10000; i++)
    {
        bgprocesses[i] = -12;
    }
    pdir_set = 0;
    L = CreateEmptyList();
    List2 = CreateEmptyList2();
    FILE *fp = fopen("./history.txt", "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    if (fp != NULL)
    {
        while ((read = getline(&line, &len, fp)) != -1)
        {
            hist_cnt++;
            line[strlen(line) - 1] = '\0';
            InsertAtFront(&L, line);
        }
    }
    bg_cnt = 0;
    while (1)
    {
        process_id = pid_myshell;
        signal(SIGCHLD, child_check);
        signal(SIGINT, ctrl);
        signal(SIGTSTP, ctrlz);
        //bg_check();
        prompt(invoke);
        read_command();
        //execute();
        invoke = 1;
        //printf("%d ",hist_cnt);
        //PrintList(L);
    }
    return 0;
}
