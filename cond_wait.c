#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <time.h>

/*
Scrivere un programma che crea n threads.
Ogni thread deve cercare di accedere a questo vettore di size (n^2)/2. Quando il vettore è pieno si attiva
il thread n+1 che legge il vettore e indica ogni thread quante volte ha avuto accesso al vettore.
*/
void * scrittore(void * arg);

void * supervisore(void * arg);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int n;
int pos=0;
int *vect;
int *occorrenze;

int main (int argc, char **argv)
{
	srand(time(NULL));
	if (argc != 2)
	{
		printf("Errore input\n");
		return -1;
	}
	n = atoi(argv[1]);
	vect = malloc(sizeof(int)*((n*n)/2));
	occorrenze = malloc(sizeof(int)*(n));
	pthread_t threads[n+1];
	int index[n], i;
	for (i=0;i<n;i++)
	{
		occorrenze[i]=0;
	}
	for (i=0;i<n;i++)
	{
		index[i] = i;
		pthread_create(&threads[i],NULL,scrittore,(void *)&index[i]);
	}
	pthread_create(&threads[n],NULL,supervisore,NULL);

	
	for(i=0;i<n+1;i++)
	{
		pthread_join(threads[i],NULL);
	}

	return 0;

}

void * scrittore(void * arg)
{
	int x = *(int*)arg;
	printf("sono il thread %d \n",x);
	while (1)
	{
	pthread_mutex_lock(&mutex);

	if (pos > (((n*n)/2))-1)
		{
			pthread_cond_signal(&cond);
			pthread_mutex_unlock(&mutex);
			pthread_exit((void *)0);
		}

	vect[pos]=rand()%10;
	//printf("vect[%d] = %d \n",pos, vect[pos]);
	occorrenze[x]= occorrenze[x]+1;
	pos++;
	pthread_mutex_unlock(&mutex);
	sleep(1);
	
	}


}

void * supervisore(void * arg)
{
	int i;
	
	while (1)
	{
	pthread_mutex_lock(&mutex);
	printf("pos = %d, n = %d\n",pos, n );

	while(((n*n)/2) > pos)
		{
			printf("sono in attesa\n");
			pthread_cond_wait(&cond, &mutex);
		}
	for (i =0; i<n;i++)
	{
		printf("il processo %d ha scritto %d volte\n",i,occorrenze[i]);
	}
	for (i=0;i<((n*n)/2);i++)
	{
	printf("vettore = %d\n",vect[i]);
	}
	pthread_mutex_unlock(&mutex);
	pthread_exit((void*)0);
	}

}