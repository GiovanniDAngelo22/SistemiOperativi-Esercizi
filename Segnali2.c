#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>

			/*• Scrivere	un	programma	in	C	e	Posix sotto	Linux	che,	preso	un	argomento	
			intero	positivo	da	riga	di	comando,	gestisca	la	seguente	situazione:	
			• genera	due	figli	A	e	B	e
			- se	l'argomento	è	PARI	invia	un	segnale	SIGUSR1	alla	ricezione	del	quale	il	
			figlio	A	calcola	il	cubo	del	numero	passato	come	argomento	da	linea	di	
			comando,	mentre	il	figlio	B	stampa	un	messaggio	di	arrivederci	e	
			termina.
			- se	l'argomento	è	DISPARI	invia	un	segnale	SIGUSR2	alla	ricezione	del	
			quale	il	figlio	B	calcola	il	reciproco	del	numero	passato	come	argomento,		
			attende	per	un	numero	di	secondi	pari	al	doppio	del	numero	passato	
			come	argomento	ed	invia	un	segnale	SIGUSR1	al	processo	A	dopodiché	
			termina	l'esecuzione.	Il	figlio	A,	invece,	attende	la	ricezione	del	segnale	
			SIGUSR1,	stampa	un	messaggio	e	termina.*/

void cubo();
void stampa();
void reciproco();

static int x;

int main (int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Input non valido\n");
		return -1;
	}
	x = atoi(argv[1]);
	if (x<0)
	{
		printf("Valore negativo\n");
		return -1;
	}
	int pid1, pid2;
	if ((pid1=fork())==0)
	{
		//figlio 1
		if (x%2 == 0)
		{
			signal(SIGUSR1, cubo);
		}
		else
		{
			signal(SIGUSR1, stampa);

		}
		pause();
		exit(0);

	}
	if ((pid2=fork())==0)
	{
		//figlio 2
		if (x%2 == 0)
		{
			signal(SIGUSR1, stampa);
		}
		else
		{
			signal(SIGUSR2,reciproco);
			pause();
			sleep(x*2);
			kill(pid1,SIGUSR1);
			exit(0);

		}
		pause();
		exit(0);
	}
	if (pid1 >0 && pid2 >0)
	{
			//padre
		sleep(1);
		if (x%2==0)
		{
			kill(pid1,SIGUSR1);
			kill(pid2,SIGUSR1);
		}
		else
		{
			kill(pid2,SIGUSR2);
		}
		wait(NULL);
		wait(NULL);
		printf("I due figli sono morti\n");

	}
	return 0;

}

void cubo()
{
	x=x*x*x;
	printf("x = %d\n", x);
}

void stampa()
{
	printf("Sono il figlio con PID = %d, arrivederci!\n", getpid());
}

void reciproco()
{
	int y;
	y = 1/x;
	printf("reciproco di x = %d\n",y);
}



