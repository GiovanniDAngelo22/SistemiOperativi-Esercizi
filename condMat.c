#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

void * func (void * arg);

int **mat;
int x;
int riga =0;
int colonna=0;

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main (int argc, char **argv)
{
	if (argc != 2 )
	{
		printf("Errore input\n");
		exit(-1);
	}
	int n = atoi(argv[1]),i;
	int flag;
	int index[n];
	pthread_t threads[n];
	mat = malloc(sizeof(int*)*5);
	for (i=0;i<5;i++)
	{
	mat[i]=malloc(sizeof(int)*5);
	}

	for(i=0;i<n;i++)
	{
		index[i] = i;
		pthread_create(&threads[i],NULL,func,(void*)&index[i]);
	}
	for (i=0;i<25;i++)
	{
		sleep(1);
		pthread_mutex_lock(&mutex);
		x = rand()%100+1;
		pthread_cond_signal(&cond);
		printf("Sono il processo padre, ho creato: %d\n",x);
		pthread_mutex_unlock(&mutex);
	}


	for(i=0;i<n;i++)
	{
		pthread_join(threads[i],NULL);
	}
	free(mat);
	
}

void * func (void * arg)
{
	int index = *(int*) arg;
	int i,j;
	int occorrenze=0;
	while (1)
	{
	pthread_cond_wait(&cond,&mutex);
	if (riga == 5)
	{
		printf("sono il processo %d ho stampato %d volte\n",index, occorrenze);
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex);
		pthread_exit((void*) 0);
	}
	mat[riga][colonna] = x;
	occorrenze++;
	colonna++;
	if (colonna == 5)
	{
	 riga++;
	 colonna=0;
	}
	if (riga == 5)
	{
	 	pthread_mutex_unlock(&mutex);
	 	pthread_cond_signal(&cond);
		for (i=0;i<5;i++)
		{
		for (j=0;j<5;j++)
			{
					printf("%d ",mat[i][j]);
			}
			printf("\n");
		}
		printf("sono il processo %d ho scritto %d volte\n",index, occorrenze);
		pthread_exit((void*) 0);
	}

	pthread_mutex_unlock(&mutex);
	}
}