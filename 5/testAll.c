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

int main ()
{
	int *p;
	
	p = (int *) malloc ( 100 * sizeof (int *) );
free (p);
	p = (int *) malloc ( 10 * sizeof (int *) );

/*
void free ( void *ptr )
void *malloc ( size_t size )
void *calloc ( size_t nelem, size_t elsize )
void *realloc ( void *ptr, size_t size )
*/
return 0;
}
