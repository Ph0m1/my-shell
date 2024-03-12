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
#define YELLOW "\33[1;32;33m"
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

void readline(char* argv[]);
void truedir(char* path);
char *formatPath;

int main(int argc, char *argv[])
{
    // getit();

    char **arg = (char**)malloc(sizeof(char*)*Max);
    while (1)
    {
        printf("\n");
        getid();
        readline(arg);
        if(strcmp(arg[0],"cd")==0) mycd(arg);
    }
    free(formatPath);
}


void mycd(char *arg[])
{
    char *path;
    path = getcwd(NULL, 0);
    if (strcmp(arg[1],"~") == 0)
    {
        char*home=getenv("HOME");
        chdir(home);
        // free(home);
    }
    else if (strcmp(arg[1],"-") == 0)
    {
        // puts(formatPath);
        char currentPath[Max];
        strcpy(currentPath,formatPath);
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
    char *path = NULL;
    path =  getcwd(NULL,0);
    truedir(path);
    
    if(strstr(path,pwd->pw_dir)){
        
    }
    //获取当前时间
    time_t t;
    time(&t);
    struct tm *tm;
    tm = localtime(&t);
    printf(BLUE "# "BLUE2"%s"NONE " @ " GREEN"%s"NONE" in "YELLOW"%s"NONE" [%d:%d:%d]\n",pwd->pw_name,hostname,path,tm->tm_hour,tm->tm_min,tm->tm_sec);
    printf(RED"$ "NONE);
    free(path);
    fflush(stdout);
}

void readline(char *argv[])
{
    char temp[Max];
    fgets(temp, Max, stdin);
    char *tok = strtok(temp, " \n");
    int i = 0;
    
    while (tok != NULL && i < Max) {
        argv[i] = strdup(tok);
        tok = strtok(NULL, " \n");
        i++;
    }
    argv[i] = NULL; 
}

void truedir(char* path)
{
    char *token = getenv("HOME");
    char *p = NULL;
    int len1 = strlen(token);
    int len2 = strlen(path);
    p = strstr(path,token);
    if(p == NULL) return;
    sprintf(path,"~%s",p+len1);
}
