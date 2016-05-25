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
};

/********************************
        FUNCIONS PRIVADES 
********************************/
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

/**
 * Busca si hi ha algun element lliure amb l'espai demanat
 * Aprofita el trajecte, per si no hi ha element, en *last escriu l'últim element
 */
p_block __find_free_best_fit ( p_block *last, size_t size )
{
	p_block current, bestFit;

	bestFit = __find_free_block ( last, size );
	if ( bestFit )
	{ // Arribats aquest punt, el last no te sentit.
		current = bestFit->next;
		while ( current && ( bestFit->size != size ) )
		{ // Si el tamany reclamat es el mateix, llavors no cal continuar
			if ( ( current->free == IS_FREE ) && ( current->size >= size ) && ( current->size < bestFit->size ) )
				bestFit = current;
			current = current->next;
		}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


/*
Sumes el tamany total
poses la estructura
Actualitzes l'estructura
	Vigilar si no hi ha espai
*/



// Millora de com "dividir" l'espai
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
	p_block current;
	current = __return_pointer_block ( ptr );
	if ( current ) // Controlant el cas NULL
	{
		current->free = IS_FREE;
		__free_next	( current );
		__free_previous	( current );
	}
}

/**
 * Funció malloc de <libstd>
 *
 * Un intent de fer un malloc útil en C
 */
void *malloc ( size_t size )
{
	p_block block, last;

	if ( size <= 0 ) return NULL;

	if ( global_base )
	{
		block = __find_free_best_fit ( &last, size ); // Definim last
		if ( block ) block->free = IS_NOT_FREE; // Em canviat a block, el important aqui es aquest
		else
		{
			block = __request_space ( last, size );
			if ( !block ) return NULL;
		}
	} else
	{ // Primer cas, quan mai s'ha reservat memoria
		block = __request_space ( NULL, size );
		if ( !block ) return NULL;
		global_base = block;
	}
return block +1;
}

/**
 * Funció calloc de <libstd>
 *
 * Un intent de fer un calloc útil en C
 */
void *calloc ( size_t nelem, size_t elsize )
{
	void *ptr;
	size_t size = nelem * elsize;

	ptr = malloc ( size );
	if ( ptr == NULL ) return NULL;

	memset ( (char *)ptr, 0, size );
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
	void *new;
	p_block block;
	if ( ptr )
	{ // Controlem el cas null
		block = __return_pointer_block ( ptr );
		if ( block->size < size )
		{
			new = malloc ( size );
			memcpy ( new, ptr, block->size );

			free ( ptr ); // Petita millora Vs. block->free = IS_FREE;

			ptr = new;
		}
		return ptr;
	}
return malloc ( size );
}
