#include "rw_pid.h"

int mm;

int pidP;
int pidH;

int whilemain;

// Que fer quan pasa un minut, no fem res, ja que ho fara tot el main.
void minut () { }

// Que fer quan et volen eliminar
void killing ()
{	whilemain = 0; }


int main ()
{
// Diem quins senyals volem fer cas
	signal ( SIGCONT, minut		);
	signal ( SIGTERM, killing	);

// Escrivim el nostre pid, si hi ha un problema, ho diem i acabem.
	writepid ( "minutos.pid");

// Espera a rebre nova senyal
pause ();

// Ara toca llegir de principal i hores, si hi ha un problema, ho diem i acabem.
	if ( readpid ( "principal.pid",	&pidP, "minutos" ) ) return 1;
	if ( readpid ( "horas.pid",	&pidH, "minutos" ) ) return 1;


// Inicialitzem les variables per entrar dins el while, i activem l'event
	mm = 0;
	whilemain = 1;

// Comenza el programa en si
	while ( whilemain )
	{
		pause ();
		if ( ++mm == 60 )
		{
			mm = 0;
			kill ( pidH, SIGCONT );
		} else
			kill ( pidP, SIGUSR2 );
	}
return 0;
}
