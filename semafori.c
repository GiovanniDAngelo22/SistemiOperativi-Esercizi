#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <time.h>
sem_t *sem_put, *sem_get;

char c;

void * produce (void * arg)
{
	int i = *(int *)arg;
	while(i >0 )
	{
		sem_wait(sem_put);
		c = (rand()%(122+1-97)) +97;
		printf("Ho scritto: %c\n",c);
		sem_post(sem_get);
		i--;
	}
	pthread_exit((void *)0 );

}

void * consume (void * arg)
{
	int i = *(int *)arg;
		while(i >0 )
	{
		sem_wait(sem_get);
		printf("Ho letto: %c\n",c);
		sem_post(sem_put);
		i--;
	}
	pthread_exit((void *)0 );
}

int main (int argc, char **argv)
{
	srand(time(NULL));
	pthread_t p1, p2;
	int ciclo = 5;
	sem_put = sem_open("put",O_CREAT,0777,1);
	sem_get = sem_open("get",O_CREAT,0777,0);

	pthread_create(&p1,NULL,produce,(void *)&ciclo);
	pthread_create(&p2,NULL,consume,(void *)&ciclo);

	pthread_join(p1,NULL);
	pthread_join(p2,NULL);




	return 0;
}
