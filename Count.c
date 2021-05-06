#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/file.h>
#define N 1000
#define MaxThread 50
pthread_t ntid[MaxThread];

typedef struct $
{
	int indice;
	int offset;
	int fine;
	int risultato;
	char x;
	char *testoDaVisionare;
} Testo;

void printids(const char *s)
{
	pid_t pid;
	pthread_t tid;
	pid=getpid();
	tid=pthread_self();
	printf("%s pid %u tid %lu \n", s, (pid_t) pid, (unsigned long) tid);
}
void * thr_fn(void * arg)
{
    printids("nuovo thread: ");
	Testo * t = (Testo *) arg;
	int i;
	t->risultato = 0;
	for (i=t->offset;i<=t->fine;i++)
	{
		if (t->x == t->testoDaVisionare[i])
		{
			t->risultato++;
		}
	}
	printf("%d\n",t->risultato);

	return ((void*)0);
}

int main (void)
{

	int risultato=0,n=4;
	Testo t[n];
	int fd, i=0, size;
	char c, testo[N],x='c';
	fd = open("Lorem", O_RDONLY);
	while (read(fd,&c,1)==1)
	{
		testo[i]=c;
		i++;
	}
	size = strlen(testo);
	int err;
	for (i=0;i<n;i++)
	{
		t[i].indice=i;
		t[i].offset = (size/n) * i;
		t[i].fine = (size/n) *(i+1)-1;
		t[i].x= x;
		t[i].testoDaVisionare = testo;
		err = pthread_create(&ntid[i],NULL,thr_fn,(void *) &t[i]);
		if (err!= 0)
		{
		fprintf(stderr, "NON POSSO CREARE IL THREAD : %s \n", strerror(err));
		exit(1);
		}
	}
	for (i=0;i<n;i++)
	{
		pthread_join(ntid[i],NULL);
	}
	printids("thread principale:");
	for (i=0; i<n;i++)
	{
		risultato = risultato + t[i].risultato;
	}
	printf("risultato = %d\n",risultato );
	exit(0);
}