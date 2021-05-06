#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>



int main (int argc, char **argv)
{
	if (argc != 2)
	{
		return 0;
		printf("Errore nel ricevimento dell'argomento\n");
	}
	char path[20];
	int fd = STDOUT_FILENO;
	int pipes[2][2];
	pipe(pipes[1]); // comunicazione tra figlio 2 e 1
	pipe(pipes[0]); // comunicazione tra figlio 1 e padre
	pid_t pid1,pid2;
	if (pid1=fork() == 0)
	{
		//figlio 1


		if (pid2=fork() == 0)
		{
			//figlio 2
			close(pipes[0][0]);
			close(pipes[0][1]);
			close(pipes[1][0]);
			dup2(pipes[1][1],1);
			close(pipes[1][1]);
			
			execlp("ls","ls",NULL);
			exit(0);

		}
		close(pipes[1][1]);
		close(pipes[0][0]);
		dup2(pipes[1][0],0);
		dup2(pipes[0][1],1);
		close(pipes[1][0]);
		close(pipes[0][1]);

		execlp("grep", "grep","-e", argv[1], NULL);
		exit(0);
	}
			//padre
		close(pipes[0][1]);
		close(pipes[1][0]);
		close(pipes[1][1]);
		dup2(pipes[0][0],0);
		close(pipes[0][0]);
		execlp("sort","sort", "-r",NULL);
	return 0;

}