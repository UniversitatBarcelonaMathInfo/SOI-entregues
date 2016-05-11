#include "common.h"

#include <string.h> /* strlen */
#include <stdio.h> /* sprintf */

// Variables glovals que necessitem
int ss, mm, hh;
char buffer[100]; // Si volguessim ser mes exactes, amb poc mes de 50 funcionaria
// Els declarem aqui, ja que el killing
int pidS;
int pidM;
int pidH;

void showString ( char * input )
{
	sprintf ( buffer, input );
	write (1, buffer, strlen (buffer) );
}

/************************* Funcions d'events *************************/
// Si pasa un segon, incrementem la variable
void segons ()
{	ss++; }

// Si pasa un minut, incrementa els minuts i posa a zero els segons
void minuts ()
{
	ss = 0; // Ho fem per no tenir que controlar-ho tot a minuts
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
{
	sprintf ( buffer, "%2d:%2d:%2d\n", hh, mm, ss );
	write (1, buffer, strlen (buffer) );
}
void killing ()
{
showString ( "Acabant els altres procesos\n" );
	kill ( pidS, SIGTERM );
	kill ( pidM, SIGTERM );
	kill ( pidH, SIGTERM );
showString ( "Finalitzat principal correctament\n" );
exit ( 0 );
}

int main ()
{

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

// Comenza el programa en si
	while ( 1 )
		pause ();
	
return 0;
}
