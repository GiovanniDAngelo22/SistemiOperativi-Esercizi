#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

int n;
int ***mat;

void * minimo(void * arg)
{
	int min,i,j=0;
	int index = *(int*)arg;
	int *risultato;
	risultato = malloc(sizeof(int));
	min = mat[index][0][0];
	for(i=0;i<3;i++)
	{

		if (mat[index][i][j] < min)
			min = mat[index][i][j];
		j++;

	}
	*risultato = min;
	return risultato;

}
int main (int argc,char *argv[])
{
	
	int i,j,k;
	void *ris;
	if (argc!=2)
	{
		printf("errore numero input \n");
		exit(-1);
	}
	n = atoi(argv[1]);
	pthread_t thread[n];
	int index[n],risultato[n];
	mat = malloc(sizeof(int**)*n);
	for (i=0;i<n;i++)
	{
		mat[i] = malloc(sizeof(int*)*3);
		for (j=0;j<3;j++)
		{
			mat[i][j]=malloc(sizeof(int)*3);
		}
	}

	for (i=0;i<n;i++)
		{
			printf("matrice %d : \n",i);
			for(j=0;j<3;j++)
			{
				for (k=0;k<3;k++)
				{
					mat[i][j][k] = rand()%100;
					printf("%d ",mat[i][j][k]);
				}
				printf("\n");
			}
		}

	for(i=0;i<n;i++)
	{
		index[i]=i;
		pthread_create(&thread[i],NULL,minimo,(void *)&index[i]);
	}


	for(i=0;i<n;i++)
	{
		pthread_join(thread[i],&ris);
		risultato[i] = *(int*)ris;
		printf("minimo %d-esimo = %d\n",i,risultato[i]);
	}



	return 0;
}