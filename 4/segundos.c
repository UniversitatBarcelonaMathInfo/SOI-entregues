#include <unistd.h> /* alarm, pause */
#include <signal.h> /* signal */
#include <sys/types.h> /* kill */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#include <stdio.h>

void segon ()
{
	printf ("Segon\n");
}

int main ()
{
	int fd; // Descriptor d'ell mateix
	int pid;

	signal ( SIGALRM, segon );
	signal ( SIGCONT, segon );

	pid = getpid ();

	remove ( "segundos.pid");
	fd = open ( "segundos.pid",
		O_WRONLY | O_CREAT | O_TRUNC,
		S_IRUSR);// | S_IWUSR | S_IRGRP | S_IROTH); // Permisos
	write ( fd, &pid, sizeof (int) );
	close ( fd );

	pause ();
	// Llegeix a fitxer
	while ( 1 )
	{
		alarm (1);
		pause ();
		//kill
	}
}
