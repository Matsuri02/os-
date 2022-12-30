#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int main()
{
    pid_t p1,p2;
    int status;
    p1=fork();
    if(!p1)//子进程
    {
         printf("子进程进程号：%d\n",getpid());
         printf("子进程休眠5秒\n");
         sleep(5);
         printf("子进程结束\n");
         exit(0);
    }
    else //父进程
    {
         p2=wait(&status);
         printf("父进程进程号：%d\n子进程进程号：%d，返回参数：%d\n",getpid(),p2,status);
    }
    return 0;
}
