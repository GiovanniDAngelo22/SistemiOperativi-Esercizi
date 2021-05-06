#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>

sem_t *sem_crea, *sem_rec;
int contatore=0,limite;
int vittima=0;

void * creatore(void * arg);
void * ricevitore(void * arg);

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Errore input\n");
		return -1;
	}
	sem_crea = sem_open("crea",O_CREAT,0777,1);
	sem_rec = sem_open("rec",O_CREAT,0777,0);
	limite = atoi(argv[1]);
	pthread_t pthreads[3];
	pthread_create(&pthreads[0],NULL,creatore,(void *)0);
	pthread_create(&pthreads[1],NULL,creatore,(void *)0);
	pthread_create(&pthreads[2],NULL,ricevitore,(void *)0);
	sleep(1);

	pthread_join(pthreads[0],NULL);
	pthread_join(pthreads[1],NULL);
	pthread_join(pthreads[2],NULL);

	printf("termino il programma\n");
	return 0;
}

void * creatore(void * arg)
{

	while (1)
	{
	sem_wait(sem_crea);
  
	if (limite <= contatore)
	{
		sem_post(sem_crea);
		pthread_exit((void*) 0);
	}
	contatore++;
	printf("%d\n",vittima );
	vittima = vittima + rand()%11;
	if (limite <= contatore)
	{
		sem_post(sem_rec);
		sem_post(sem_crea);
		pthread_exit((void*) 0);

	}
	sem_post(sem_crea);
	}
	printf("sono uscito dal while LOL\n");


}

void * ricevitore(void * arg)
{

	sem_wait(sem_rec);
	printf("valore finale = %d\n",vittima);
	sem_post(sem_rec);
	pthread_exit((void*)0);

	
}