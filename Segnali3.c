#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <wait.h>
#include <sys/stat.h>
#include <fcntl.h>


int fd;
int x,y=1;
char buffer[20];
void handlerFather();
void handlerChild();

int main (int argc, char *argv[])
{
	int i;
	char temp[30];
	if (argc != 2)
	{
		printf("ERRORE\n");
		return -1;
	}
	x = atoi(argv[1]);
	fd = open("temp.txt", O_CREAT | O_TRUNC | O_RDWR, 0777);
	int pid1;
	if ((pid1=fork())==0)
	{
		//sono il figlio
		signal(SIGUSR1,handlerChild);
		for (i=1; i<x;i++)
		{
			pause();
			kill(getppid(),SIGUSR1);
		}
		exit(0);
	}
	else
	{
		sleep(1);
		signal(SIGUSR1,handlerFather);
		//sono il padre
		sprintf(temp,"%d",y);
		write(fd, &temp, strlen(temp));
		for(i=1;i<x;i++)
		{
			kill(pid1,SIGUSR1);
			pause();
		}
		wait(NULL);
		exit(0);
	}
}

void handlerChild()
{
	lseek(fd,0,SEEK_SET);
	read(fd, &buffer,sizeof(buffer));
	printf("Sono il figlio, ho ricevuto %s\n",buffer);
	lseek(fd,0,SEEK_SET);

}

void handlerFather()
{
	y++;
	char temp[30];
	sprintf(temp,"%d",y);
	write(fd, &temp, strlen(temp));
	printf("Sono il padre, ho scritto %d\n",y);
}