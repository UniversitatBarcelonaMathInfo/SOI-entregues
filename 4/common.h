/*
Llibreria que tenen en comu:
	- principal
	- segundos
	- minutos
	- horas
*/

// Llibreria usada per poder fer anar: /alarm/ i /pause/
#include <unistd.h>

// Llibreria usada per poder fer anar: /signal/
#include <signal.h>

// Llibreria usada per poder fer anar: /kill/
#include <sys/types.h>

// Llibreria usada per poder fer anar: /exit/
#include <stdlib.h>

// Llibreria per a poder escriure i llegir el pid en els fitxers demanats
#include "rw_pid.h"
