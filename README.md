# SHELL 
### How to run ?
```sh
make
./a.out
```
### main.c
This is the main file for the execution of the shell. It loads history for the shell, looks after the initialisation and also has the signal handlers for SIGCHLD , SIGINT and SIGSTP signals. Functions prompt() and read_command() are invoked to execute the shell.
### bg.c
Functions 
```sh
void bg(char *process_name, char **args, bool flag)
```
This function executes both foreground and background processes. To execute a background process type '&' at the end of command. For a background process flag is set to true otherwise false.
### cd.c
```sh
void cd()
```
This function executes the cd command for the shell.
### echo.c
```sh
void echo()
```
This function executes the echo command which prints the text supplied to it.
### execute.c
```sh
bool check()
void call()
void execute(char* cmd)
```
bool check()- Checks for the redirection operators ('>','<','>>') and sets the input and output modes according to the requirement. It is called in void call().

void call()- This function calls functions to check for redirection operators followed by calling an appropriate function to execute a given command.

void execute(char *cmd) - This parses a single command string to obtain the command name and various arguments.
### fgbg.c
```sh
void bg_cmd()
void fg_cmd()
```
void bg_cmd()- This function implements *bg* command. This commands accepts a job number and the changes the state of the job corresponding to the input from Stopped to Running. An error will be thrown if no such job exists.

void fg_cmd()- This function implements *fg* command . This commands accepts a number as job number and brings the running or stopped background job corresponding to the job number to the foreground, and changes its state to running. An error will be thrown if no such job exists.
### headers.h
This file contains all the required header files , global variables and function definitions.
### history.c
```sh
void history()
```
This function executes *history* and *history -num* commands. Prints the last 10 commands or given number of commands.
### jobs.c
```sh
void jobs()
```
This function implements the jobs command with -r and -s flags. It prints all background jobs along with pid and job number and status(Running / stopped). If -r flag is used, only running processes will be listed. Similarly, if -s flag is used, only stopped processes will be listed.
### linked.c and linked.h
These files contains declarations and utilities of linked lists. These were used internally to implement history.
### ls.c
```sh
void ls()
void ls_list()
void ls_s()
```
void ls()- This function sets the flags and variables for ls functionality and calls one of the other two functions accordingly.
-a flag is handled in both the functions.
void ls_list() - This function executes -l flag 
void ls_s() - This function executes ls without -l flag.
### makefile
This is used to run the shell . It has the compilation commands.
### pinfo.c
```sh
void pinfo()
```
This function executes the pinfo command. It is used to get the process information of the current process by default or a process specified by its pid which is given as argument.
### prompt.c
```sh
void prompt()
```
This function displays a prompt before user enters a command. It displays username, hostname, and the current working directory.
### pwd.c
```sh
void pwd()
```
This function implements *pwd* which displays the absolute path to current working directory.
### readcommand.c
```sh
void read_command()
```
This function reads a single line command , saves history , parses the string to separate commands by ';' , implements pipes and calls the execute() function.
### repeat.c
```sh
void repeat()
```
This function implements the repeat command. The command is responsible for executing the given instruction multiple times. 
### signal.c
```sh
void sig()
```
This function implements the *sig* command which takes a job number and signal number as arguments respectively and sends the given signal to the respective job. It will throw an error if no such job exists.