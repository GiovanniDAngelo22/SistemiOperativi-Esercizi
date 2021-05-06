#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>

int main (int argc, char **argv)
{

	if (argc != 2)
	{
		printf("Errore input\n");
		exit(-1);
	}
	int pipes[2][2];
	pipe(pipes[1]);
	pipe(pipes[0]);

	int fd,n;
	pid_t pid1,pid2;
	bool flag=true;
	char stringa[81];
	fd = open(argv[1], O_RDONLY, O_EXCL);
	if (pid1 = fork() == 0)
	{

	}
	else
	{
		if (pid2 = fork() == 0)
		{

		}
		close(pipes[1][0]);
		close(pipes[1][1]);
		close(pipes[0][0]);
		

		while (n = read(fd,&stringa,sizeof(stringa)-1) > 0)
		{


				

		}


	}





	printf("sono fuori dal while\n");
}