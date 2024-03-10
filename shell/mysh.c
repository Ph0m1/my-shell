#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#define Max 2048
#define BULE
#define YELLOW
#define GREEN
#define RED
#define NONE

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
    getit();

    while (1)
    {
        colorfulprint();
        if(argv[0] == "cd") mtcd(argv);
    }
}

char path[Max];

void mycd(char *argv[])
{
    if(argv[0] != "cd")
        return;
    char *currentPath = getcwd(NULL,0);
    if(argv[1] == "~")
    {
        char*home=getenv("HOME");
        chdir("/home");
    }
    if(argv[1] == "-")
    {

    }
    if(chdir(argv[1]) == -1){
        printf("Cannot move to %s", argv[1]);
    }
    memcpy(path,currentPath);
}