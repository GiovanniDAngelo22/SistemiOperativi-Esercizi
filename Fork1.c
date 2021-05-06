#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <signal.h>
/*Si realizzi la seguente interazione di processi:
Il sistema consiste di 3 processi: un processo padre(P1) che provvede alla creazione di 2 processi figli (P11 e P12);
dopo la creazione dei figli, provvede a generare 20 numeri compresi tra 50 e 100 e un messaggio di terminazione,
scrivendoli su una pipe; P11 e P12 attendono da P1 un segnale SIGUSR1 di inizio di attività;
P11 e P12 prelevano in modo competitivo i numeri dalla pipe e li trascrivono,
ciasciuno su un proprio file; P1 deve attendere il completamento dei figli.*/

void waito(int sig)
{
	printf("Segnale ricevuto  \n");
}
int main()
{
	int i;
	pid_t pid11=1, pid12;
	signal(SIGUSR1,waito)
	pid11=fork();
	if (pid11>0)
	{
		pid12=fork();
	}
	if (pid11 ==0 || pid12==0)
	{
		printf("sono arrivato qui\n");
		signal(SIGUSR1,waito);
		return 0;

	}
	kill(pid12,SIGUSR1);
	kill(pid11,SIGUSR1);

	printf("sono il padre\n");
	return 0;
}