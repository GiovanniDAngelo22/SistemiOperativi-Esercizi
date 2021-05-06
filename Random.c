#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <unistd.h>

#define MAX_THREAD 50
pthread_t thread[MAX_THREAD];
int var=0;
void * threadFunc (void * arg)
{
	int x;
	x = rand() % 9;
	x++;
	sleep(x);
	var++;
	printf("Primo thread: %d tempo aspettato = %d\n",var, x);
	return ((void *)0);
}

int main(void)
{
	int n,i;
	printf("Inserisci il numero di thread: \n");
	scanf("%d",&n);
	for (i=0;i<n;i++)
	{
		pthread_create(&thread[i],NULL,threadFunc,NULL );
	}
	for(i=0;i<n;i++)
	{
		pthread_join(thread[i],NULL);
	}
	return 0;
}