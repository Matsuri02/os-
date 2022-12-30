#include<unistd.h>
#include<stdio.h>
int main()
{
	printf("A代表父进程输出信息；B代表子进程输出信息。\n");
	pid_t p=fork();
	if(p)
        {
		printf("A父进程进程号：%d\n",getpid());
                printf("A创建的子进程进程号：%d\n",p);
		printf("A暂时挂起父进程以便ps检查结果(10s)：\n");
		sleep(10);
		printf("A父进程结束\n");
	}
        else
        {
		printf("B子进程进程号：%d\n",getpid());
		printf("B父进程未结束时，子进程的父进程进程号：%d\n",getppid());
		printf("B暂时挂起子进程以便ps检查结果(10s)：\n");
		sleep(10);
		printf("B父进程结束后，子进程的父进程进程号：%d\n",getppid());
		printf("B子进程继续挂起，同时再用ps检查结果(10s)：\n");
                sleep(10);       //让子进程更晚结束
		printf("B子进程结束\n");
	}
	return 0;
}

