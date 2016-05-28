#include <unistd.h>
#include <stdint.h>
#include <string.h>

#include <stdio.h>

#define META_SIZE	sizeof ( struct m_block )
#define ENOMEM		(void*) -1
#define IS_NOT_FREE	0
#define IS_FREE		1

typedef struct m_block* p_block;

// Punter global, tot i ser aixi, no vull que ningú més que jo el canviin.
static void *global_base=NULL;
static size_t nom;
static int debug=1;
static int debugPrint=1;

/* Teoria
Equivalens
current->free
(*current).free
*/


/* Com treballem:
__nom Significa que declarem una funció privada per a nosaltres
	- No estaria al fitxer .h
*/

// Declarem una estructura
struct m_block // Tamany de 24 = 8*3 // hi ha 7 bytes que sobren
{
	size_t		size;	// Tamany 8, amb el tamany total que te reservat
	struct m_block	*next;	// Tamany 8, amb el seguent del mateix
	uint8_t		free;	// Tamany 1, amb 0: Hi ha coses, amb ≠0 no hi ha res
	size_t		nom;	// Per debugeixar millor i fer-ho mes entenedor
};

/********************************
        FUNCIONS PRIVADES 
********************************/
void __print ()
{
if ( debugPrint )
{
	p_block current = global_base;
	int i = 0;
	while ( current )
	{
		printf ( "%3d n: %3zu -size: %5zu\tstat: %d\tpunter: %p\n", i++, current->nom, current->size, current->free, current );
		current = current->next;
	}
}
}

/**
 * Funció que donant el punter donat al usuari recuperem el m_block
 */
p_block __return_pointer_block ( void *p )
{
	p_block ptr;
	if ( p ) // Controlem que sigui valid
	{
		ptr = (p_block) p;
		return ptr -1;
	}
	return NULL;
}

/**
 * Posa el present en free
 * I si el seguent se pot adjuntar, l'adjunta
 *
 * Fa les comprovacions necessaries per a evitar errors
 */
void __free_next ( p_block current )
{
	p_block next;
	if ( current )
	{ // Comprova entrada vàlida
		next = current->next;
		if ( next )
		{ // Comprova que tingui un element seguent
			if ( next->free == IS_FREE )
			{
				current->size += next->size + META_SIZE;
				current->next = next->next;
			}
		}
	}
}

/**
 * Si l'anterior esta en free. Llavors l'adjunta
 *
 * Fa les comprovacions necessaries per a evitar errors
 */
void __free_previous ( p_block current )
{
	p_block previous;
	previous = global_base;

	if ( current && ( current != global_base ) )
	{ // Comprovem que la entrada sigui valida. I no sigui el primer element.

// Ens dediquem a buscar l'element anterior.
		while ( (previous) && (previous->next != current) )
			previous = previous->next;

		if ( previous )
		{ // Per evitar que no existeixi. Tot i que si la entrada es correcta, no hauria de passar mai.
			if ( previous->free == IS_FREE )
				__free_next ( previous );
		}
	}
}

/**
 * Busca l'existencia d'un element lliure amb la memòria indicada.
 *
 * Per si mai no ha obtingut resultat, a *last indica on es troba l'últim element.
 * Aixo es fa per aprofitar el recorregut que em fet.
 */
p_block __find_free_block ( p_block *last, size_t size )
{
	p_block current = global_base;
	while ( current && !( current->free && (current->size >= size) ) )
	{ // Sortira: Quan ho haguem trobat o ja no queden més elements per a recorrer
		*last = current;
		current = current->next;
	}
return current;
}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void __comprovar_tamany ( p_block current, size_t size )
{
	size_t aux;
	p_block newBlock;
	void *p;
if ( debug )
{
	printf ( "NOM: %zu\n", current->nom );
printf ( "Entrat comprovat Tamany: %p\n", current );

	if ( !current )
		printf ( "He trobat on peta\n" );
	else printf ( "preocupa\n" );

	if ( current->size > size )
	{ // Comprovem que pugui reservar-se un nou block
printf ( "Lloc 1\n" );
		aux = current->size - size;
		if ( aux >= META_SIZE )
		{
printf ( "Lloc 2\n" );
			p = current +1; // punter del current + META_SIZE
			p += size; // El lloc mes les posicions
			newBlock = p;
	//		newBlock = current + size; // Posicionem el bloc

printf ( "Lloc 3\n" );
			newBlock->free = IS_FREE;
			newBlock->size = aux - META_SIZE;
			newBlock->next = current->next;
			newBlock->nom = nom++;

printf ( "Lloc 4\n" );
			current->next = newBlock;
			current->size = size;
printf ( "Feta millora\n" );
		}
	}
printf ( "Sortit\n" );
}
}

/**
 * Busca si hi ha algun element lliure amb l'espai demanat
 * Aprofita el trajecte, per si no hi ha element, en *last escriu l'últim element
 *
 * Definim el millor, com l'element mes petit que conte el desitjat
 */
p_block __find_free_best_fit ( p_block *last, size_t size )
{
	p_block current, bestFit;

	bestFit = __find_free_block ( last, size );
	if ( bestFit )
	{ // Arribats aquest punt, el last no te sentit. I sabem que el resultat es positiu.
		current = bestFit->next;
		while ( current && ( bestFit->size != size ) )
		{ // Si el tamany reclamat es el mateix, llavors no cal continuar
			if ( ( current->free == IS_FREE ) && ( current->size >= size ) && ( current->size < bestFit->size ) )
				bestFit = current;
			current = current->next;
		} // Comprovem si podem crear un nou element ( exces de memoria no usada )
		__comprovar_tamany ( bestFit, size );
	}
return bestFit;
}

/**
 * Reserva el nombre de bytes demanats per size
 * Suposem que last, és l'últim block definit fins el moment
 *
 * Retornara el m_block arreclant el seu contingut
 * Si mai no pot fer-ho, retornarà un NULL
 */
p_block __request_space ( p_block last, size_t size )
{
	p_block block;
	block = sbrk (0);

	if ( sbrk(size + META_SIZE) == ENOMEM ) return NULL;
	if ( last ) last->next = block;

	block->size = size;
	block->next = NULL;
	block->free = IS_NOT_FREE;
	block->nom = nom++;
return block;
}

/*********************************
        FUNCIONS PUBLIQUES
*********************************/
/*
Problema 1
-Posem el atribut free a 1.
-Em definit "__return_pointer_block" que retorna l'adreça del bloc de meta informació donat un apuntador de dades.
-Tenim en compte el apuntador NULL
*/
/**
 * Funció que allibera el punter donat pel malloc.
 *
 * Nota: no eliminarà la informació que hi ha fins que es faci un malloc.
 */
void free ( void *ptr )
{
printf ( "Free" );
	p_block current;
	current = __return_pointer_block ( ptr );
	if ( current ) // Controlant el cas NULL
	{
printf ( ": %zu", current->nom );
		current->free = IS_FREE;
		__free_next	( current );
		__free_previous	( current );
	}
printf ( "\n" );
__print ();
}

/**
 * Funció malloc de <libstd>
 *
 * Un intent de fer un malloc útil en C
 */
void *malloc ( size_t size )
{
	printf ( "Malloc" );
	p_block block, last;

	if ( size <= 0 ) return NULL;

	if ( global_base )
	{
		block = __find_free_best_fit ( &last, size ); // Definim last
		if ( block )
		{ // Si ha trobat
			block->free = IS_NOT_FREE; // Em canviat a block, el important aqui es aquest
		} else
		{
			if ( last->free == IS_FREE )
			{ // Necessariament per __find_free_block, size > last->size
				if ( sbrk (size - last->size) == ENOMEM )
					return NULL;
				block = last;
				block->free = IS_NOT_FREE;
				block->size = size;
			} else
				block = __request_space ( last, size );
			if ( !block ) return NULL;
		}
	} else
	{ // Primer cas, quan mai s'ha reservat memoria
		block = __request_space ( NULL, size );
		if ( !block ) return NULL;
		global_base = block;
		nom = 0;
		block->nom = nom++;
	}
if ( block )
	printf ( ": %zu", block->nom );
printf ( "\n" );
__print ();
return block +1;
}

/**
 * Funció calloc de <libstd>
 *
 * Un intent de fer un calloc útil en C
 */
void *calloc ( size_t nelem, size_t elsize )
{
printf ( "calloc:\n" );
	void *ptr;
	size_t size = nelem * elsize;

	ptr = malloc ( size );
	if ( ptr == NULL ) return NULL;

	memset ( (char *)ptr, 0, size );
__print ();
return ptr;
}

/**
 * Funció realloc de <libstd>
 *
 * Un intent de fer un realloc útil en C
 */
 //!!!!!!!!!!!!!!!!! Error, en el cas que demani menys memoria, crear un nou block
void *realloc ( void *ptr, size_t size )
{
printf ( "realloc:\n" );
	void *new;
	p_block block;
	if ( ptr )
	{ // Controlem el cas null
		block = __return_pointer_block ( ptr );
		__free_next ( block ); // fem el tamany mes gran possible
		if ( block->size < size )
		{
			new = malloc ( size );
			memcpy ( new, ptr, block->size );

			free ( ptr ); // Petita millora Vs. block->free = IS_FREE;

			ptr = new;
		} else if ( block->size > size )
			__comprovar_tamany ( block, size );
		return ptr;
	}
__print ();
return malloc ( size );
}
