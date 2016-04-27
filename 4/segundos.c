#include <unistd.h> /* alarm, pause */
#include <signal.h> /* signal */
#include <sys/types.h> /* kill */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


#include <stdio.h>

int ss;
int pidP;

void segon ()
{
	alarm (1);
	ss++;
	if ( ss == 60 )
	{
		ss = 0;
		//kill a minuts !!!!
	}
	printf ("SS %d\n", pidP);
	kill ( pidP, SIGUSR1 );
}
/* Ja que sino, el SIGCONT no et fa sortir del pause */
void start () { ss = 0;}

int main ()
{
	int fd; // Descriptor d'ell mateix
	int pid;
//	int pidM; // Id dels minuts !!!!
//	int pidP; // Id del principal !!!!
	char *buffer;

	signal ( SIGALRM, segon );
	signal ( SIGCONT, start );

	pid = getpid ();

	remove ( "segundos.pid");
	fd = open ( "segundos.pid",
		O_WRONLY | O_CREAT | O_TRUNC,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH); // Permisos
	if ( fd == -1 )
	{
		write (2, "ERROR, segundos no ha pogut guardar la seva informacio\n", 55); // Comptat amb el 'v' de vim.
		//return 1;
	}
	write ( fd, &pid, sizeof (int) );
	close ( fd );
	printf ( "My pid segundos es: %d\n", pid );

pause (); // Espera a rebre senyal per a executar-se

// Llegir el id del principal
	fd = open ( "principal.pid", O_RDONLY );
	if ( fd == -1 )
	{
		buffer = "ERROR, segundos no ha pogut llegir de principal\n";
		write (2, buffer, strlen (buffer) ); // Comptat amb el 'v' de vim.
		return 1;
	}
	read (fd, &pidP, sizeof (int) );
	close ( fd );

	printf ( "S:El meu id: %d\n", pid );
	printf ( "S;El meu id llegit: %d\n", pidP );

	alarm (1);
	int i = 4;
	while ( i-- )
	{
		pause ();
		kill ( pidP, SIGUSR1 );
	}
}
