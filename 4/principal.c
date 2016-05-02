#include <unistd.h> /* alarm, pause */
#include <signal.h> /* signal */
#include <sys/types.h> /* kill */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#include <stdio.h>
#include <string.h>
#include <stdio.h>

#include "rw_pid.h"

int ss, mm, hh;
void continuar ()
{
	hh++;
	if (hh == 24) hh = 0;
	printf ("Calla! ");
}
void ssIncrement ()
{
	ss++;
	printf ("Calla segons: ");
}

int main ()
{
	int pidS;
	int pidM;
	int pidH;

	signal ( SIGCONT, continuar );
	signal ( SIGUSR1, ssIncrement );

printf ("My pid principal: %d\n", getpid());//!!!!

	if ( writepid ( "principal.pid" ) ) return 1;

pause (); // Espera a rebre nova senyal
	showString ( "Llegint el pid dels demes\n" );

	if ( readpid ( "segundos.pid",	&pidS, "principal" ) ) return 1;
	if ( readpid ( "minutos.pid",	&pidM, "principal" ) ) return 1;
	if ( readpid ( "horas.pid",	&pidH, "principal" ) ) return 1;

	showString ( "Activant segons, minuts i hores des de principal\n" );
// Ara toca llegir de segons, minuts i hores
/*
	fd = open ( "minutos.pid", O_RDONLY );
	if ( fd == -1 )
	{
		buffer = "ERROR, principal no ha pogut llegir minutos.pid\n O_RDONLY\n";
		write (2, buffer, strlen (buffer) );
		return 1;
	}
	read (fd, &pidM, sizeof (int) );
	close ( fd );

	fd = open ( "horas.pid", O_RDONLY );
	if ( fd == -1 )
	{
		buffer = "ERROR, principal no ha pogut llegir horas.pid\n O_RDONLY\n";
		write (2, buffer, strlen (buffer) );
		return 1;
	}
	read (fd, &pidH, sizeof (int) );
	close ( fd );
*/

printf ("Principal te id segundos: %d\n", pidS); //!!!!
printf ("Principal te id minutos: %d\n", pidM); //!!!!
printf ("Principal te id horas: %d\n", pidH); //!!!!
	// Aqui Minuts i hores !!!!
	kill ( pidS, SIGCONT );
	while (1)
	{
		printf ( "While principal\n" );
		pause ();
	}
}
