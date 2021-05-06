#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <unistd.h>

#define MAX_THREAD 50
pthread_t thread[MAX_THREAD];
int n;
int **mat;
void * threadFunc (void * arg)
{


	int i;
	int *riga = (int *) arg;
	int *sum = malloc(sizeof(int));
	*sum=0;
	if ((*riga)%2==0)
	{
		for (i=0;i<n;i+=2)
		{
			*sum = mat[*riga][i] + *sum;
		}
	}
	else 
	{
		for (i=1;i<n;i+=2)
		{
			*sum = mat[*riga][i] + *sum;
		}
	}

	return sum;
}

int main(void)
{
	int *iesimi;
	int i,j;
	printf("Inserisci il numero di thread: \n");
	scanf("%d",&n);
	mat = (int**)malloc(sizeof(int*)*n);
	for (i=0;i<n;i++)
	{
		mat[i]= (int*)malloc(sizeof(int)*n);
	}
	void * sum[n];
	for (i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			mat[i][j] = rand()%255;
			printf("%d ",mat[i][j]);
		}
		printf("\n");
	}
	iesimi = malloc(sizeof(int)*n);

	for (i=0;i<n;i++)
	{
		iesimi[i] = i;
		pthread_create(&thread[i],NULL,threadFunc, &iesimi[i]);
	}
	for(i=0;i<n;i++)
	{
		pthread_join(thread[i],&sum[i]);
	}
	for (i=0;i<n;i++)
	{
	printf("riga %d = %d\n",i,*(int*)sum[i]);
	}

	return 0;
}