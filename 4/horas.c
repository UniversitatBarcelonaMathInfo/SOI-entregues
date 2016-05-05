#include "rw_pid.h"

int pidP;
int whilemain;

// Que fer quan pasa una hora, no fem res, ja que ho fara tot el main.
void hora () { }

// Que fer quan et volen eliminar
void killing ()
{	whilemain = 0; }


int main ()
{
// Diem quins senyals volem fer cas
	signal ( SIGCONT, hora		);
	signal ( SIGTERM, killing	);

// Escrivim el nostre pid, si hi ha un problema, ho diem i acabem.
	writepid ( "horas.pid");

// Espera a rebre nova senyal
pause ();

// Ara toca llegir de principal i hores, si hi ha un problema, ho diem i acabem.
	if ( readpid ( "principal.pid",	&pidP, "minutos" ) ) return 1;


// Inicialitzem les variables per entrar dins el while, i activem l'event
	whilemain = 1;

// Comenza el programa en si
	while ( whilemain )
	{
		pause ();
		kill ( pidP, SIGCONT );
	}
return 0;
}
