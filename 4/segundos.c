#include <unistd.h> /* alarm, pause */
#include <signal.h> /* signal */
#include <sys/types.h> /* kill */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


#include <stdio.h>

#include "rw_pid.h"

// Variables glovals que necessitem
int ss;
int whilemain;
int pidP, pidM;

// Que fer quan pasa un segon, cridat per ell mateix, el SIGALARM, i per continuar en el SIGCONT
void segon ( int i )
{	alarm (1); }

// Que fer quan et volen eliminar
void killing ()
{	whilemain = 0; }


int main ()
{
// Diem quins senyals volem fer cas
	signal ( SIGALRM, segon		);
	signal ( SIGCONT, segon		);
	signal ( SIGTERM, killing	);

// Escrivim el nostre pid, si hi ha un problema, ho diem i acabem.
	if ( writepid ( "segundos.pid" ) ) return 1;

// Espera a rebre nova senyal
pause ();

// Ara toca llegir de principal i minuts, si hi ha un problema, ho diem i acabem.
	if ( readpid ( "principal.pid",	&pidP, "segundos" ) ) return 1;
	if ( readpid ( "minutos.pid",	&pidM, "segundos" ) ) return 1;


// Inicialitzem les variables per entrar dins el while, i activem l'event
	ss = 0;
	whilemain = 1;

// Comenza el programa en si
	while ( whilemain )
	{
		pause ();

		if ( ++ss == 60 )
		{
			ss = 0;
			kill ( pidM, SIGCONT );
		} else
			kill ( pidP, SIGUSR1 );
	}
return 0;
}
