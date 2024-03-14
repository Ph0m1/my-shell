#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>
#include <pwd.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include <fcntl.h>
#include <wait.h>

#define Max 2048
#define BLUE "\033[1;32;34m"
#define BLUE2 "\033[;32;34m"
#define YELLOW "\33[1;32;33m"
#define GREEN "\033[0;32;32m"
#define GREEN2 "\033[0;35;32m"
#define RED "\033[1;32;31m"
#define NONE "\033[0m"

int cin = 0;
char *formatPath;

void showhistory();
// 获取用户组信息
void getid(char *str);
// 屏蔽信号
void getit();
// 输出
void colorfulprint();
// cd
void mycd(char *argv[]);

void exec(char *arg[]);

int readltok(char *stdinn, char *argv[]);
void truedir(char *path);

int main(int argc, char *argv[])
{
    getit();
    char *readlineonscreen = (char *)malloc(sizeof(char) * Max);
    char *stdinn = NULL;
    while (1)
    {
        printf("\n");
        getid(readlineonscreen);
        char *arg[Max] = {NULL};
        stdinn = readline(readlineonscreen);
        add_history(stdinn);
        if (stdinn == "\n" || stdinn == NULL)
            continue;
        char *command = NULL;
        int cnt = 0;
        strcpy(command,stdinn);
        if(strstr(command, "|")){

        }
        else if(strstr(command,"<")){

        }
        else if(strstr(command,">>"))
        {

        }
        else if(strstr(command,">"))
        {
            
        }
        
        int cincount = readltok(stdinn, arg);
        if (arg[0] == NULL)
            continue;
        if (strcmp(arg[0], "cd") == 0 || strcmp(arg[0], "chdir") == 0)
            mycd(arg);
        else
            exec(arg);

        fflush(stdout);
    }
    free(stdinn);
    free(readlineonscreen);
    free(formatPath);
}

void mycd(char *arg[])
{

    char *path;
    path = getcwd(NULL, 0);
    if (strcmp(arg[1], "~") == 0)
    {
        char *home = getenv("HOME");
        chdir(home);
        // free(home);
    }
    else if (strcmp(arg[1], "-") == 0)
    {
        // puts(formatPath);
        char currentPath[Max];
        strcpy(currentPath, formatPath);
        truedir(currentPath);
        puts(currentPath);
        chdir(formatPath);
    }
    else
    {
        chdir(arg[1]);
    }
    formatPath = path;
}

void getid(char *str)
{
    // 获取当前用户
    uid_t uid;
    uid = getuid();
    struct passwd *pwd;
    pwd = getpwuid(uid);

    // 获取主机名
    char hostname[Max + 1];
    if (gethostname(&hostname[0], Max) == -1)
    {
        perror("gethostname");
        exit;
    }

    // 获取当前所在目录
    char *path = NULL;
    path = getcwd(NULL, 0);
    truedir(path);

    // 获取当前时间
    time_t t;
    time(&t);
    struct tm *tm;
    tm = localtime(&t);
    sprintf(str, "\001" BLUE "# " BLUE2 "%s" NONE " @ " GREEN "%s" NONE " in " YELLOW "%s" NONE " [%d:%d:%d]\n\001%s", pwd->pw_name, hostname, path, tm->tm_hour, tm->tm_min, tm->tm_sec, uid == 1 ? RED "# " NONE : RED "$ " NONE"\002");
    free(path);
    fflush(stdout);
}

int readltok(char *stdinn, char *argv[])
{
    char *tok = strtok(stdinn, " \n");
    if (tok == NULL)
        return 0;
    int i = 0;

    while (tok != NULL && i < Max)
    {
        argv[i] = strdup(tok);
        tok = strtok(NULL, " \n");
        i++;
    }
    argv[i] = NULL;
    cin = i + 1;
    return cin;
}

void truedir(char *path)
{
    char *token = getenv("HOME");
    char *p = NULL;
    int len1 = strlen(token);
    int len2 = strlen(path);
    p = strstr(path, token);
    if (p == NULL)
        return;
    sprintf(path, "~%s", p + len1);
}

void getit()
{
    signal(SIGINT, SIG_IGN);
    signal(SIGHUP, SIG_IGN);
}


void mydup()
{
    int fd1;
    int fd2;
}

void exec(char *arg[])
{
    int pd = fork();
    if (pd == 0)
    {
        if (execvp(arg[0], arg) < 0)
        {
            perror("command not found");
            exit(1);
        }
    }
    else
        wait(NULL);
    return;
}