#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
void* th_fn1(void *arg)
{
	for(int i=1;i<=1000;i++)
        {
		printf("A:%d\n",i);
		sleep(1);
	}
}
void* th_fn2(void *arg)
{
	for(int i=1000;i>0;i--)
        {
		printf("B:%d\n",i);
		sleep(1);
	}
}
int main()
{
	int err;
   	pthread_t  tid1,tid2;
   	if(err=pthread_create(&tid1,NULL,th_fn1,NULL))
        {
		perror("pthread_create error");
	}
   	if(err=pthread_create(&tid2,NULL,th_fn2,NULL))
        {
		perror("pthread_create error");
	}
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	return 0;
}


