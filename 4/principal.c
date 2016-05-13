#include "rw_pid.h"
/*
Us de:
	sigset_t mask, oldmask;
	sigemptyset ( &mask );
	sigaddset ( &mask, SIGTERM );
	sigprocmask ( SIG_BLOCK, &mask, &oldmask );
	sigsuspend ( &oldmask );
	sigprocmask ( SIG_UNBLOCK, &mask, NULL );
Per evitar el problema que rebi la interrupcio quan no toca.
Ho fem per evitar que es demani que acabi el proces i aquest no acabi, i ho fem aixi per a poder sortir per la sortida normal.
S'ha tret gracies al Lluis Garrido que ens ha ajudat amb aquest link:
http://www.gnu.org/software/libc/manual/html_node/Sigsuspend.html
*/

// Variables glovals que necessitem globals
int ss, mm, hh;
int whilemain;

// Si pasa un segon, incrementem la variable
// No cal el control, ja que quan rebi el de minuts o hores es posara automaticament a zero
// Aixo ho podem fer gracies a que "segundos" no envia sempre senyal, nomes ho fa quan segons ha d'incrementar,
// sino "segundos" enviara la senyal nomes a "minutos"
void segons ()
{	ss++; }
// Si pasa un minut, incrementa els minuts i posa a zero els segons
void minuts ()
{
	ss = 0;
	mm++;
}
// Cas que posa a zero els minuts i controlem les hores
void hores ()
{
	ss = mm = 0;
	if ( ++hh == 24 ) hh = 0;
}
// Mostra el temps transcorregut
void show ()
{	showTime ( ss, mm, hh ); }
// Canvia la variable whilemain per poder sortir normalment del programa
void killing ()
{	whilemain = 0; }
	
int main ()
{
	int pidS;
	int pidM;
	int pidH;

// Variables per a rebre interrupcions
	sigset_t mask, oldmask;

// Diem quins senyals volem fer cas
	signal ( SIGCONT, hores		);
	signal ( SIGUSR1, segons	);
	signal ( SIGUSR2, minuts	);
	signal ( SIGALRM, show		);
	signal ( SIGTERM, killing	);

// Escrivim el nostre pid, si hi ha un problema, ho diem i acabem.
	if ( writepid ( "principal.pid" ) ) return 1;

// Espera a rebre nova senyal
pause ();

// Ara toca llegir de segons, minuts i hores, si hi ha un problema, ho diem i acabem.
	showString ( "Llegint el pid dels demes\n" );
	if ( readpid ( "segundos.pid",	&pidS, "principal" ) ) return 1;
	if ( readpid ( "minutos.pid",	&pidM, "principal" ) ) return 1;
	if ( readpid ( "horas.pid",	&pidH, "principal" ) ) return 1;

// Ara toca activar segons, minuts i hores
	showString ( "Activant segons, minuts i hores des de principal\n" );
	kill ( pidS, SIGCONT );
	kill ( pidM, SIGCONT );
	kill ( pidH, SIGCONT );


// Inicialitzem les variables per entrar dins el while
	ss = mm = hh = 0;
	whilemain = 1;

// Comenza el programa en si
	while ( whilemain )
		pause ();
	
showString ( "Acabant els altres procesos\n" );
	kill ( pidS, SIGTERM );
	kill ( pidM, SIGTERM );
	kill ( pidH, SIGTERM );
showString ( "Finalitzat principal correctament\n" );
return 0;
}
