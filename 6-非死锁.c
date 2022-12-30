#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<sys/syscall.h>
#include<semaphore.h>
#define thinker_num 5
pthread_mutex_t s[thinker_num];	//筷子
sem_t s_full;			//最多(thinker-1)个人同时开始吃饭

float getRandTime()
{	
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC,&ts);
        return 0.001*(ts.tv_nsec%400)+0.1;
}

void* thinker(void* arg)
{
	int index=(int)arg;
	int index2=(index+1)%thinker_num;
	float sleepTime;
        while(1)
        {
		sleepTime=getRandTime();
		printf("哲学家%ld正在思考，需时%fs\n",syscall(SYS_gettid),sleepTime);
		sleep(sleepTime);
                sleepTime=getRandTime();
                printf("哲学家%ld正在休息，需时%fs\n",syscall(SYS_gettid),sleepTime);
                sleep(sleepTime);
		sem_wait(&s_full);
		pthread_mutex_lock(&s[index]);
		printf("哲学家%ld拿起筷子%d\n",syscall(SYS_gettid),index);
		pthread_mutex_lock(&s[index2]);
		sleepTime=getRandTime();
		printf("哲学家%ld拿起筷子%d,%d，开始吃饭，需时%fs\n",syscall(SYS_gettid),index,index2,sleepTime);
		sleep(sleepTime);
		pthread_mutex_unlock(&s[index2]);
		printf("哲学家%ld放下筷子%d\n",syscall(SYS_gettid),index2);
		pthread_mutex_unlock(&s[index]);
		printf("哲学家%ld放下筷子%d,%d\n",syscall(SYS_gettid),index,index2);
		sem_post(&s_full);
        }
}

int main()
{
	sem_init(&s_full,0,thinker_num-2);	
	pthread_t id[thinker_num];
	for(int i=0;i<thinker_num;++i)
		pthread_create(&id[i],NULL,(void*)thinker,(void*)i);
	for(int i=0;i<thinker_num;++i)
		pthread_join(id[i],NULL);
	return 0;
}

