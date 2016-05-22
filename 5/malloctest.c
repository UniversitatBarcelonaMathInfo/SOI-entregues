#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main ()
{
	char *ptr_one, *ptr_five;
	ptr_one = (char *) malloc ( sizeof (char) );

	if ( ptr_one == NULL )	return 1;

	*ptr_one = 'C';
	printf ( "%c\n", *ptr_one );

	free ( ptr_one );

	ptr_five = (char *) malloc ( 5* sizeof (char) );
	if ( ptr_five == NULL )	return 1;

	*ptr_five = 'C';
	ptr_five[1] = 'A';
	ptr_five[2] = 'S';
	ptr_five[3] = 'A';
	ptr_five[4] = '\0';
	printf ( "%s\n", ptr_five );
	memset ( ptr_five, 'i', 4 );
	printf ( "%s\n", ptr_five );
printf ( "apunta: %p\n", ptr_five );
	free (ptr_five); // ERROR !!!!!!
printf ( "apunta: %p\n", ptr_five );
printf ( "Aqui hauria de petar...\n" );
	memset ( ptr_five, 'i', 4 );
	printf ( "%s\n", ptr_five );

	ptr_one = (char *) malloc ( sizeof (char) );

	if ( ptr_one == NULL )	return 1;

	*ptr_one = 'C';
	printf ( "%c\n", *ptr_one );

	free (ptr_one);
return 0;
}
