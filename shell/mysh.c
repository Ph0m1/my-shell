#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>
#include <pwd.h>
#include <sys/types.h>

#define Max 2048
#define BLUE "\033[0;32;34m"
#define BLUE2 "\033[;32;34m"
#define YELLOW "\33[0;32;33m"
#define GREEN "\033[0;32;32m"
#define GREEN2 "\033[0;35;32m"
#define RED "\033[1;32;31m"
#define NONE "\033[0m"

// 获取用户组信息
void getid();
// 屏蔽信号
void getit();
// 输出
void colorfulprint();
// cd
void mycd(char *argv[]);
//>
void mydup();
//>>
void mydup2();
//<
void mydup3();

int main(int argc, char *argv[])
{
    // getit();

    // while (1)
    {
        getid();
        if(argv[0] == "cd") mycd(argv);
    }
}

char *formatPath;
void mycd(char *arg[])
{
    char *path;
    path = getcwd(NULL, 0);
    if (strcmp(arg[1],"~") == 0)
    {
        char*home=getenv("HOME");
        chdir(home);
        free(home);
    }
    else if (strcmp(arg[1],"-") == 0)
    {
        puts(formatPath);
        chdir(formatPath);
    }
    else
    {
        chdir(arg[1]);
    }
    path=getcwd(NULL,0);
    formatPath = path;
    free(path);
}

void getid()
{
    //获取当前用户
    uid_t uid;
    uid = getuid();
    struct passwd *pwd;
    pwd = getpwuid(uid);
    
    //获取主机名
    char hostname[Max+1];
    if(gethostname(&hostname[0],Max)==-1)
    {
        perror("gethostname");
        exit;
    }
    
    //获取当前所在目录
    char * path = getcwd(NULL,0);
    time_t t;
    time(&t);
    struct tm *tm;
    tm = localtime(&t);
    printf(BLUE "# "BLUE2"%s"NONE " @ " GREEN"%s"NONE" in "YELLOW"%s"NONE" [%d:%d:%d]\n",pwd->pw_name,hostname,path,tm->tm_hour,tm->tm_min,tm->tm_sec);
    printf(RED"$ "NONE);
}
