#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <signal.h>
#include <time.h>
#include <grp.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "linked.h"
#define NAME_SIZE 1000
#define PATH_SIZE 5000
bool flag;
int arg_num , cmd_cnt , hist_cnt,bg_cnt , pdir_set;
pid_t pid_myshell , process_id;
bool left , right , dright;
int in_file, out_file;
int reserve_inp_file , reserve_output_file ;
List L;
char *cmds[40];
char * pipe_cmds[40];
char *args[100];
char* cmd_name;
int bgprocesses[10000];
char bgpname[10000][1000];
struct Node2 * List2;
char home_dir[PATH_SIZE];
char prev_dir[PATH_SIZE];
char curr_dir[PATH_SIZE];
pid_t shell_pgid;
struct termios shell_tmodes;
int shell_terminal;
int shell_is_interactive;
int main ();
void prompt(int invoke);
void read_command();
void execute();
void call();
void cd();
void ls();
void echo();
void bg(char* process_name , char**args , bool flag);
void history();
void bg_check();
void fg_cmd();
void bg_cmd();
void baywatch();
void print_init(int col);
void jobs();
void pinfo();
void repeat();
void pwd();
void sig();
char get_key();