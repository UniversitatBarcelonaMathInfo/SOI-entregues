#include "common.h"

// Variables glovals que necessitem
// Es per a poder controlar la sortida correcta al proces.
int whilemain;

/************************* Funcions d'events *************************/

// Volem que la crida de segon generi la seguent crida.
// Ja que en principi el programa pot durar indefinidament.
void segon ( int i )
{	alarm (1); }

// Canvia la variable per a sortir normalment del programa
void killing ()
{	whilemain = 0; }


/************************* Proces principal *************************/
int main ()
{
// Variables per a recordar el pid de principal i minuts. Tambe segons, per a tenir-ho controlat.
	int pidP;
	int pidM;
	int ss;

// Variables per a rebre interrupcions de sortida de proces.
	sigset_t mask, oldmask;

// Inicialitzant whilemain per continuar adequadament.
	whilemain = 1;

// Diem quins senyals volem fer cas:
	signal ( SIGALRM, segon		);
	signal ( SIGCONT, segon		);
	signal ( SIGTERM, killing	);

// Escrivim el nostre pid, si hi ha un problema, ho diem i acabem.
	if ( writepid ( "segundos.pid" ) ) return 1;


// Espera a rebre nova senyal. Suposarem que si s'ha enviat una senyal abans, no i farem cas.
// El usuari ho podra saber perque no ha aparegut per pantalla el "Llegint el pid dels demes".
// I normalment, aixo no pasara, ja que ha d'inicialitzar tots els altres procesos.
pause ();

// Ara toca llegir de principal i minuts, si hi ha un problema, ho diem i acabem.
	if ( readpid ( "principal.pid",	&pidP, "segundos" ) ) return 1;
	if ( readpid ( "minutos.pid",	&pidM, "segundos" ) ) return 1;


// Inicialitzem les variables abans d'entrar dins el while.
	ss = 0;

// Ajustant l'espera a senyals.
	sigemptyset ( &mask );
	sigaddset ( &mask, SIGTERM );

// Ara fara que nomes rebra la senyal de SIGTERM quan estigui dins de 'sigsuspend'.
	sigprocmask ( SIG_BLOCK, &mask, &oldmask );

// Comenza el programa en si
	while ( whilemain )
	{
// Es un pause, menys per SIGTERM, que nomes el rebra quan la crida sigui feta.
		sigsuspend ( &oldmask );

// Nomes envia un sol senyal per segon.
// Aixo es degut a haver-me trobat errors:
//	- 0: 0:59 >> 0: 0:60
//	- 0: 0:59 >> 0: 1: 1
// Per evitar aquests dos possibles errors, nomes enviem una senyal.
		if ( ++ss == 60 )
		{
			ss = 0;
			kill ( pidM, SIGCONT );
		} else
			kill ( pidP, SIGUSR1 );
	}
return 0;
}
