#include "headers.h"

void ls_s(char *path, bool a)
{
    struct dirent *d;
    DIR *dir = opendir(path);
    if (!dir)
    {
        if (errno == 2)
        {
            perror("Directory does not exists");
        }
        else
        {
            perror("Unable to read directory");
        }
        return;
    }
    while ((d = readdir(dir)) != NULL)
    {
        if (d->d_name[0] == '.')
        {
            if (a)
                printf("%s\n", d->d_name);
        }
        else
        {
            printf("%s\n", d->d_name);
        }
    }
}
void ls_list(char *path, char a)
{
    struct dirent *d;
    DIR *dir = opendir(path);
    if (!dir)
    {
        if (errno == 2)
        {
            perror("Directory does not exists");
        }
        else
        {
            perror("Unable to read directory");
        }
        return;
    }
    long long int size = 0;
    while ((d = readdir(dir)) != NULL)
    {
        char filep[strlen(path) + strlen(d->d_name) + 4];
        sprintf(filep, "%s/%s", path, d->d_name);
        struct stat s;
        int ret = stat(filep, &s);
        if (ret < 0)
        {
            perror("Error reading the directory!");
            return;
        }
        else
        {
            if (d->d_name[0] == '.')
            {
                if (a)
                    size += (long long int)(s.st_blocks / 2);
            }
            else
            {
                size += (long long int)(s.st_blocks / 2);
            }
        }
    }
    printf("total %lld\n", size);
    dir = opendir(path);
    while ((d = readdir(dir)) != NULL)
    {
        char filep[strlen(path) + strlen(d->d_name) + 4];
        sprintf(filep, "%s/%s", path, d->d_name);
        struct stat s;
        int ret = stat(filep, &s);
        if (ret < 0)
        {
            perror("Error reading the directory!");
            return;
        }
        else
        {
            mode_t m = s.st_mode;
            time_t tim = s.st_mtime;
            struct passwd *userid = getpwuid(s.st_uid);
            struct group *grpid = getgrgid(s.st_gid);
            char print[12];
            if (S_ISDIR(m))
            {
                print[0] = 'd';
            }
            else
            {
                print[0] = '-';
            }
            if ((m & S_IRUSR))
            {
                print[1] = 'r';
            }
            else
            {
                print[1] = '-';
            }
            if ((m & S_IWUSR))
            {
                print[2] = 'w';
            }
            else
            {
                print[2] = '-';
            }
            if ((m & S_IXUSR))
            {
                print[3] = 'x';
            }
            else
            {
                print[3] = '-';
            }
            if ((m & S_IRGRP))
            {
                print[4] = 'r';
            }
            else
            {
                print[4] = '-';
            }
            if ((m & S_IWGRP))
            {
                print[5] = 'w';
            }
            else
            {
                print[5] = '-';
            }
            if ((m & S_IXGRP))
            {
                print[6] = 'x';
            }
            else
            {
                print[6] = '-';
            }
            if ((m & S_IROTH))
            {
                print[7] = 'r';
            }
            else
            {
                print[7] = '-';
            }
            if ((m & S_IWOTH))
            {
                print[8] = 'w';
            }
            else
            {
                print[8] = '-';
            }
            if ((m & S_IXOTH))
            {
                print[9] = 'x';
            }
            else
            {
                print[9] = '-';
            }
            print[10] = '\0';
            char time[PATH_SIZE];
            struct tm timeprint;
            localtime_r(&tim, &timeprint);
            strftime(time, PATH_SIZE, "%b %d %Y %H:%M", &timeprint);
            if (d->d_name[0] == '.')
            {
                if (a)
                    printf("%s\t%ld\t%s\t%s\t%ld\t%s\t%s\n", print, s.st_nlink, userid->pw_name, grpid->gr_name, s.st_size, time, d->d_name);
            }
            else
            {
                printf("%s\t%ld\t%s\t%s\t%ld\t%s\t%s\n", print, s.st_nlink, userid->pw_name, grpid->gr_name, s.st_size, time, d->d_name);
            }
        }
    }
}
void ls()
{
    bool l = false, a = false, ind = false;
    char directory[PATH_SIZE];
    for (int i = 1; i < arg_num; i++)
    {
        if (args[i][0] == '-' && (args[i][1] != 'a' && args[i][1] != 'l'))
        {
            printf("ls: illegal option --%c", args[i][1]);
            return;
        }
        if (strcmp(args[i], "-l") == 0)
        {
            l = true;
        }
        else if (strcmp(args[i], "-a") == 0)
        {
            a = true;
        }
        else if ((strcmp(args[i], "-al") == 0) || (strcmp(args[i], "-la") == 0))
        {
            l = true;
            a = true;
        }
        else
        {
            strcpy(directory, args[i]);
            ind = true;
        }
    }
    if (ind != true)
    {
        if (l)
        {
            ls_list(".", a);
        }
        else
        {
            ls_s(".", a);
        }
    }
    else
    {
        for (int i = 1; i < arg_num; i++)
        {

            if (strcmp(args[i], "-a") != 0 && strcmp(args[i], "-l") != 0 && strcmp(args[i], "-al") != 0 && strcmp(args[i], "-la") != 0)
            {
                strcpy(directory, args[i]);
                if (strcmp(directory, "~") == 0)
                {
                    strcpy(directory, home_dir);
                }
                if (l)
                {
                    ls_list(directory, a);
                }
                else
                {
                    ls_s(directory, a);
                }
            }
            if (i != arg_num - 1)
                printf("\n");
        }
    }
}