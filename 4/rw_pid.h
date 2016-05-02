
/* 0 correct write pid */
// File, quin fitxer vols escriure
int writepid ( char * file );

/* 0 correct read pid */
// File, quin fitxer vols escriure
// read, a on guarda el resultat
// origin, per a saber qui el crida
int readpid ( char * file, int * read, char * origin );

/* Simplement mostra l'estring entrat */
void showString ( char * input );
