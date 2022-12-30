#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<sys/syscall.h>
#include<semaphore.h>
int share[10];	//共享缓冲区
int indexc=0;	//生产者处理的标号(临界资源)
int indexp=0;	//消费者处理的标号(临界资源)
sem_t is_empty;	//缓冲区中存在空位
sem_t is_full;	//缓冲区已满
pthread_mutex_t mutexc = PTHREAD_MUTEX_INITIALIZER;	//互斥锁
pthread_mutex_t mutexp = PTHREAD_MUTEX_INITIALIZER;     //互斥锁
void* consume(void* arg)
{
	int add=(int)arg;
        while(1)
        {
		sem_wait(&is_full);
                pthread_mutex_lock(&mutexc);
                struct timespec ts;
                clock_gettime(CLOCK_MONOTONIC, &ts);
                int data=ts.tv_nsec%1000+add;
                share[indexc]=data;
                float sleepTime=0.001*(ts.tv_nsec%900)+0.1;
                printf("生产者%ld填第%d块：%d，即将休眠%fs\n",syscall(SYS_gettid),indexc,data,sleepTime);
		indexc++;
                if(indexc>9)indexc-=10;
		pthread_mutex_unlock(&mutexc);
                sem_post(&is_empty);
                sleep(sleepTime);

        }
}

void* produce(void)
{
	while(1)
        {
		sem_wait(&is_empty);
                struct timespec ts;
                clock_gettime(CLOCK_MONOTONIC, &ts);
		float sleepTime=0.001*(ts.tv_nsec%900)+0.1;
		pthread_mutex_lock(&mutexp);
                printf("消费者%ld取第%d块：%d, 即将休眠%fs\n",syscall(SYS_gettid),indexp,share[indexp],sleepTime);
                indexp++;
                if(indexp>9)indexp-=10;
                pthread_mutex_unlock(&mutexp);
		sem_post(&is_full);
                sleep(sleepTime);
        }

}

int main()
{
	sem_init(&is_empty,0,0);//初值为0，用于同步生产者和消费者
	sem_init(&is_full,0,9);	//初值为9，表示初始缓冲区填10个满
	pthread_t idc1,idc2;
	pthread_t idp1,idp2,idp3;
	pthread_create(&idc1,NULL,(void*)consume,(void*)1000);
	pthread_create(&idc2,NULL,(void*)consume,(void*)2000);
	pthread_create(&idp1,NULL,(void*)produce,NULL);
	pthread_create(&idp2,NULL,(void*)produce,NULL);
	pthread_create(&idp3,NULL,(void*)produce,NULL);
	pthread_join(idc1,NULL);
	pthread_join(idc2,NULL);
	pthread_join(idp1,NULL);
	pthread_join(idp2,NULL);
	pthread_join(idp3,NULL);
	return 0;
}

