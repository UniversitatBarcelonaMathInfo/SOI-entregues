#include <stdlib.h>
#include <stdio.h>
/*
Idea

Fare tots els cassos

free
free endarrera
free endavant

free endavant i endarrere

Malloc
malloc petit diferents modes

calloc
realloc

I crec que ja
*/

#define TAMANY_INT 7

int main ()
{
	int i;
	int **pINT;
	
	pINT = (int **) malloc ( TAMANY_INT * sizeof (int **) );

	for ( i = 0; i < TAMANY_INT; i++ )
	{
		pINT[i] = (int *) malloc ( TAMANY_INT * sizeof (int *) );
	}

/*
void free ( void *ptr )
void *malloc ( size_t size )
void *calloc ( size_t nelem, size_t elsize )
void *realloc ( void *ptr, size_t size )
*/

malloc (0);
for ( i = 0; i < TAMANY_INT; i++ )
{
	free (pINT[i]);
}
malloc (0);
free (pINT);
malloc (0);
	pINT = (int **) malloc ( TAMANY_INT * sizeof (int **) );
	for ( i = 0; i < TAMANY_INT; i++ )
	{
		pINT[i] = (int *) malloc ( TAMANY_INT * sizeof (int *) );
	}
malloc (0);
return 0;
}
