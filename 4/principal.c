#include "common.h"
#include <string.h> /* strlen */
#include <stdio.h> /* sprintf */
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


// Variables glovals que necessitem
// Son i serveixen per a poder mostrar el temps
int ss, mm, hh;
int whilemain;

// Funcio util, ja que volem imprimir per pantalla
void showString ( char * input )
{ write (1, input, strlen (input) ); }



/************************* Funcions d'events *************************/

// Si pasa un segon, incrementem la variable.
// No cal el control, ja que quan rebi el de minuts o hores es posara automaticament a zero.
// Aixo ho podem fer gracies a que "segundos" no envia sempre senyal, nomes ho fa quan segons ha d'incrementar,
// sino "segundos" enviara la senyal nomes a "minutos".
void segons ()
{	ss++; }

// Si pasa un minut, incrementa els minuts i posa a zero els segons.
// No cal el control, ja que quan rebi el d'hores es posara automaticament a zero.
// Aixo ho podem fer gracies a que "minutos" no envia sempre senyal, nomes ho fa quan minuts ha d'incrementar,
// sino "minutos" enviara la senyal nomes a "horas"
void minuts ()
{
	ss = 0;
	mm++;
}

// Si pasa una hora, incrementem les hores i posem a zero segons i minuts.
// Cal un control d'hores, i vigilar que no sigui 24, si ho es el posarem a zero.
// Aqui cal control perque "horas", sempre envia senyal, cada hora, i no hi ha cap senyal especial per a controlar-ho.
void hores ()
{
	ss = mm = 0;
	if ( ++hh == 24 ) hh = 0;
}

// Mostra el temps transcorregut
void show ()
{
	char buffer[10];
	sprintf ( buffer, "%2d:%2d:%2d\n", hh, mm, ss );
	write (1, buffer, strlen (buffer) );
}

// Canvia la variable per a sortir normalment del programa
void killing ()
{ 	whilemain = 0; }


/************************* Proces principal *************************/
int main ()
{
// Variables per a recordar el pid de segons, minuts i hores.
	int pidS;
	int pidM;
	int pidH;

// Variables per a rebre interrupcions de sortida de proces.
	sigset_t mask, oldmask;

// Inicialitzant whilemain per continuar adequadament.
	whilemain = 1;

// Diem quins senyals volem fer cas:
	signal ( SIGCONT, hores		);
	signal ( SIGUSR1, segons	);
	signal ( SIGUSR2, minuts	);
	signal ( SIGALRM, show		);
	signal ( SIGTERM, killing	);

// Escrivim el nostre pid, si hi ha un problema, ho diem i acabem.
	if ( writepid ( "principal.pid" ) ) return 1;

// Espera a rebre nova senyal. Suposarem que si s'ha enviat una senyal abans, no i farem cas.
// El usuari ho podra saber perque no ha aparegut per pantalla el "Llegint el pid dels demes".
// I normalment, aixo no pasara, ja que ha d'inicialitzar tots els altres procesos.
pause ();

// Ara toca llegir de segons, minuts i hores, si hi ha un problema, ho diem i acabem.
showString ( "Llegint el pid dels demes\n" );
	if ( readpid ( "segundos.pid",	&pidS, "principal" ) ) return 1;
	if ( readpid ( "minutos.pid",	&pidM, "principal" ) ) return 1;
	if ( readpid ( "horas.pid",	&pidH, "principal" ) ) return 1;

// Ara toca activar segons, minuts i hores.
showString ( "Activant segons, minuts i hores des de principal\n" );
	kill ( pidS, SIGCONT );
	kill ( pidM, SIGCONT );
	kill ( pidH, SIGCONT );


// Inicialitzem les variables abans d'entrar dins el while.
// Ho fem aqui, ja que per a continuar, haura incrementat el temps. Aixi evitem aquesta hora afegida.
	ss = mm = hh = 0;

// Ajustant l'espera a senyals.
	sigemptyset ( &mask );
	sigaddset ( &mask, SIGTERM );

// Ara fara que nomes rebra la senyal de SIGTERM quan estigui dins de 'sigsuspend'.
	sigprocmask ( SIG_BLOCK, &mask, &oldmask );

// Comenza el programa en si
	while ( whilemain )
// Es un pause, menys per SIGTERM, que nomes el rebra quan la crida sigui feta.
		sigsuspend ( &oldmask );

// Realment no es necessari, pero ara, desbloqueixem el SIGTERM// Com que no es necesari, a "segundos", "minutos" i "horas" no ho poso.
	sigprocmask ( SIG_UNBLOCK, &mask, NULL );

// Aqui fa que els altres procesos acabin correctament.
showString ( "Acabant els altres procesos\n" );
	kill ( pidS, SIGTERM );
	kill ( pidM, SIGTERM );
	kill ( pidH, SIGTERM );
showString ( "Finalitzat principal correctament\n" );
return 0;
}
