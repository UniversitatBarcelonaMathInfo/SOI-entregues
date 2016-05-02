#include <unistd.h> /* getpid */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <string.h>
#include <stdio.h>

char buffer[100]; // Si volguessim ser mes exactes, amb poc mes de 50 funcionaria

/* 0 correct write pid */
// File, quin fitxer vols escriure
int writepid ( char * file )
{
	int pid;
	int fd;

	pid = getpid ();
	remove ( file );
	fd = open ( file ,
		O_WRONLY | O_CREAT | O_TRUNC, // Escriptura nomes, crear-lo si no esta, tamany a zero
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH); // U=RW, GO=R
	if ( fd == -1 )
	{
		sprintf ( buffer, "ERROR\nNo s'ha pogut guardar el pid a: %s\n", file );
		write (2, buffer, strlen (buffer) ); // Comptat amb el 'v' de vim.
		return 1;
	}
	write ( fd, &pid, sizeof (int) );
	close ( fd );
return 0;
}

/* 0 correct read pid */
// File, quin fitxer vols escriure
// read, a on guarda el resultat
// origin, per a saber qui el crida
int readpid ( char * file, int * r, char * origin )
{
	int fd;

	fd = open (file, O_RDONLY );
	if ( fd == -1 )
	{
		sprintf
		(
			buffer,
			"ERROR, %s no ha pogut llegir %s\n O_RDONLY\n",
			origin, file
		);
		write (2, buffer, strlen (buffer) );
		return 1;
	}
	read (fd, &r, sizeof (int) );
	close ( fd );
}

void showString ( char * input )
{
	sprintf ( buffer, input );
	write (1, buffer, strlen (buffer) );
}
