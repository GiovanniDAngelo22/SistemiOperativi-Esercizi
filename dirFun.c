/*
Scrivere un programma in C che prende da riga di comando 3 directory diverse. Il processo crea due figli a cui da le prime due directory(una per figlio) 
i figli dovranno scorrere i file nella directory
assegnata e trovare il file con size massimo. Nel frattempo, i figli dovranno scrivere sullo stdout il nome del file, il size e i suoi permessi. 
Inviare al padre il risultato. 
Il padre ricevuti i due risultati calcolerà il massimo fra i due e quello più grande
verrà creata una copia nella terza directory presa da riga di comando. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
	if (argc != 4)
	{
		printf(" errore input\n");
		return -1;
	}
	int err;
	mode_t mode_max;
	int max=0,max1,max2;
	char vincitore1[256],vincitore2[256];
	char nomeMax[20];
	DIR *newdir;
	struct stat *stats = malloc(sizeof(struct stat));
	struct dirent *currdir = malloc(sizeof(struct dirent));
	int pipes[2][2];
	char buffer[200];
	pipe(pipes[0]); //comunicazione con figlio 1
	pipe(pipes[1]); //comunicazione con figlio 2
	pid_t pid1,pid2;

	if ((pid1=fork())==0)
	{
		close(pipes[1][0]);
		close(pipes[1][1]);
		close(pipes[0][0]);

		err = chdir(argv[1]);
		if (err != 0)
		{
			printf("Errore nella chdir 1\n");
			exit(-1);
		}
		newdir = opendir(argv[1]);
		while ((currdir = readdir(newdir)) != NULL)
		{
			if (currdir->d_type == DT_REG)
			{
				printf("nome dir 1 = %s\n", currdir->d_name);
				stat(currdir->d_name,stats);
				printf("size = %ld\n", stats->st_size);
				if (stats->st_size > max)
				{
					strcpy(nomeMax,currdir->d_name);
					mode_max=stats->st_mode;
					max = stats->st_size;
				}
			}

		}
		printf("File massimo figlio 1= %s, size = %d, mode = %o\n", nomeMax, max, mode_max);
		printf("sono qui\n");
		//write(pipes[0][1],&max,sizeof(max));
		write(pipes[0][1],nomeMax,strlen(nomeMax));
		close(pipes[0][1]);
		exit(0);
		
	}

	if (pid1>0)
	{
		printf("sono quuuiiiiiiii\n");
		if((pid2=fork())==0)
		{

			close(pipes[0][0]);
			close(pipes[0][1]);
			close(pipes[1][0]);

			err = chdir(argv[2]);
			if (err != 0)
			{
				printf("Errore nella chdir 2\n");
				exit(-1);
			}

			newdir = opendir(argv[2]);
			while ((currdir = readdir(newdir)) != NULL)
			{
				if (currdir->d_type == DT_REG)
				{
					printf("nome dir 2 = %s\n", currdir->d_name);
					stat(currdir->d_name,stats);
					printf("size = %ld\n", stats->st_size);
					if (stats->st_size > max)
					{
						strcpy(nomeMax,currdir->d_name);
						mode_max=stats->st_mode;
						max = stats->st_size;

					}
				}
			}
			printf("File massimo figlio 2= %s, size = %d, mode = %o\n", nomeMax, max, mode_max);
			//write(pipes[1][1],&max,sizeof(max));
			write(pipes[1][1],nomeMax,strlen(nomeMax));
			close(pipes[1][1]);
			exit(0);

		}

	}
	if (pid1>0 && pid2 >0)
	{
				printf("sono arrivato prima della read\n");

		close(pipes[0][1]);
		close(pipes[1][1]);
		//read(pipes[0][0],&max1,sizeof(max1));
		read(pipes[0][0],&vincitore1,20);
		//read(pipes[1][0],&max2,sizeof(max2));
		read(pipes[1][0],&vincitore2,20);
		close(pipes[0][0]);
		close(pipes[1][0]);
		wait(NULL);
		wait(NULL);
		printf("vincitore 1 = %s\n",vincitore1);
		printf("vincitore 2 = %s\n",vincitore2);



		return 0;

	}

}
