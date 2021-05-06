#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

pthread_t ntid;
void printids(const char *s)
{
	pid_t pid;
	pthread_t tid;
	pid=getpid();
	tid=pthread_self();
	printf("%s pid %u tid %lu \n", s, (pid_t) pid, (unsigned long) tid);
}
void * thr_fn(void *arg)
{
	printids("nuovo thread: ");
	return ((void*)0);
}

int main (void)
{
	int err;
	err = pthread_create(&ntid,NULL,thr_fn,NULL);
	if (err!= 0)
	{
	fprintf(stderr, "NON POSSO CREARE IL THREAD : %s \n", strerror(err));
	exit(1);
	}
	printids("thread principale:");
	sleep(1);
	exit(0);
}