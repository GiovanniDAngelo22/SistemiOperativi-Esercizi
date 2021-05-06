#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <time.h>

int **mat;
int n;
void * sommaFunc(void * flag);



int main (int argc, char *argv[])
{

	int i,j,somma[4];
	void * ris;
	srand(time(NULL));
	printf("Inserire n dispari\n");
	scanf("%d",&n);
	if (n%2==0)
	{
		printf("numero pari, chiusura del programma\n");
		exit(0);
	}
	mat = malloc(sizeof(int*)*n);
	for (i=0;i<n;i++)
	{
		mat[i]=malloc(sizeof(int)*n);
	}
	for (i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			mat[i][j] = rand()%10;
			printf("%d",mat[i][j]);
		}
		printf("\n");
	}


	pthread_t thread[4];
	int  flag[4];
	for (i=0;i<4;i++)
	{
		flag[i] = i;
		pthread_create(&thread[i],NULL,sommaFunc,(void*) &flag[i]);
	}
	for (i=0;i<4;i++)
	{
		pthread_join(thread[i], &ris);
		somma[i] = *(int*) ris;
	}
	for (int i = 0; i < 4; ++i)
	{
		printf("somma %d = %d\n",i, somma[i]);
	}
	int max=somma[0];
	for (i=0;i<4;i++)
	{
		if (somma[i] > max)
		{
			max = somma[i];
		}
	}
	printf("max = %d\n",max);
	return 0;
}

void * sommaFunc (void * flag)
{
	int *ris = malloc(sizeof(int));
	int i,j;
	int x = *(int*) flag;
	switch(x)
	{
		case(0):
		{
			
			for (j=n-1, i=0;i<n;i++,j--)
			{
				*ris = *ris + mat[i][j];
			}
			break;
		}
		case(1):
		{
			
			for (i=0;i<n;i++)
			{
				*ris = *ris + mat[i][i];
			}
		
			break;
		}
		case(2):
		{  
			
			j= n/2;
			for (i=0;i<n;i++)
			{
				*ris = *ris + mat[i][j];
			}
			break;
		}
		case(3):
		{
			
			i= n/2;
			for (j=0;j<n;j++)
			{
				*ris = *ris + mat[i][j];
			}
			break;
		}
	}
	return ris;
}