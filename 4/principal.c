#include <unistd.h> /* alarm, pause */
#include <signal.h> /* signal */
#include <sys/types.h> /* kill */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#include <stdio.h>
#include <string.h>
#include <stdio.h>

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
	int pid;
	int pidS;
//	int pidM; !!!!
//	int pidH; !!!!
	char *buf;
	int fd;

	signal ( SIGCONT, continuar );
	signal ( SIGUSR1, ssIncrement );

	pid = getpid ();
	printf ("My pid principal: %d\n", pid);//!!!!

	remove ( "principal.pid" );
	fd = open ( "principal.pid",
		O_WRONLY | O_CREAT | O_TRUNC,
		S_IRUSR);
	if ( fd == -1 )
	{
		buf = "ERROR, principal no ha pogut guardar la seva informacio\n";
		write (2, buf, strlen (buf) );
		return 1;
	}
	write ( fd, &pid, sizeof (int) );
	close ( fd );

pause ();
// Ara toca llegir de segons, minuts i hores

	fd = open ( "segundos.pid", O_RDONLY );
	if ( fd == -1 )
	{
		buf = "ERROR, principal no ha pogut llegir segundos.pid\n O_RDONLY\n";
		write (2, buf, strlen (buf) );
		return 1;
	}
	read (fd, &pidS, sizeof (int) );
	close ( fd );
	printf ("Principal te id segundos: %d\n", pidS); //!!!!
	// Aqui Minuts i hores !!!!
	kill ( pidS, SIGCONT );
	while (1) pause ();
}
