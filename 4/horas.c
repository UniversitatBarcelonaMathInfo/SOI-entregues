#include "common.h"

// Variables glovals que necessitem
// Es per a poder controlar la sortida correcta al proces.
int whilemain;

/************************* Funcions d'events *************************/

// Que fer quan pasa una hora, no fem res, ja que ho fara tot el main.
void hora () { }

// Canvia la variable per a sortir normalment del programa
void killing ()
{	whilemain = 0; }


/************************* Proces principal *************************/
int main ()
{
// Variable per a recordar el pid de principal.
	int pidP;

// Variables per a rebre interrupcions de sortida de proces.
	sigset_t mask, oldmask;

// Inicialitzant whilemain per continuar adequadament.
	whilemain = 1;

// Diem quins senyals volem fer cas:
	signal ( SIGCONT, hora		);
	signal ( SIGTERM, killing	);

// Escrivim el nostre pid, si hi ha un problema, ho diem i acabem.
	if ( writepid ( "horas.pid" ) ) return 1;

// Espera a rebre nova senyal. Suposarem que si s'ha enviat una senyal abans, no i farem cas.
// El usuari ho podra saber perque no ha aparegut per pantalla el "Llegint el pid dels demes".
// I normalment, aixo no pasara, ja que ha d'inicialitzar tots els altres procesos.
pause ();

// Ara toca llegir de principal i hores, si hi ha un problema, ho diem i acabem.
	if ( readpid ( "principal.pid",	&pidP, "minutos" ) ) return 1;


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
		kill ( pidP, SIGCONT );
	}
return 0;
}
