#include <unistd.h>
#include <stdint.h>
#include <string.h>

#include <stdio.h>

#define META_SIZE sizeof ( struct m_block )
#define ENOMEM (void*)-1
#define IS_NOT_FREE	0
#define IS_FREE		1

typedef struct m_block* p_block;

void *global_base=NULL;

/*
Equivalens
current->free
(*current).free
*/

// Declarem una estructura
struct m_block // Tamany de 24 = 8*3 // hi ha 7 bytes que sobren
{
	size_t		size;	// Tamany 8, amb el tamany total que te reservat
	struct m_block	*next;	// Tamany 8, amb el seguent del mateix
	uint8_t		free;	// Tamany 1, amb 0: Hi ha coses, amb ≠0 no hi ha res
};

p_block return_pointer_block ( void *p )
{
	p_block ptr;
	if ( p ) // Controlem que sigui valid
	{
		ptr = (p_block) p;
		return ptr -1;
	}
	return NULL;
}

void free ( void *ptr )
{
printf ( "My free\n" );
	p_block block = return_pointer_block ( ptr );
	if ( block ) // Controlant el cas NULL
		block->free = IS_FREE;
	ptr = NULL; // Important anular el que conte...
}
// RRRR !!!!! pendent
/*
void free ( void *ptr )
{
printf ( "My free\n" );
	if ( ptr )
	{ // Controlant el cas NULL
		p_block a = (p_block) ptr;
		a[-1].free = IS_FREE;
	}
}
*/

/*
if current // Permet assegurar que hi ha informacio valida
	if free // Si esta lliure comprovem
		if current->size ≥ size
			Acabem
Tot aixo equival a: current && !( current->free && (current->size ≥ size) )
*/
//p_block find_free_block ( p_block *last, size_t size )
/*
Quan ha acabat de buscar?
	1. Si no hi ha mes block:
		- if current
	2. Si esta lliure i te espai de sobres
		- if current->free && (current->size) ≥ size

*/
p_block find_free_block ( p_block *last, size_t size )
//p_block find_free_block ( size_t size )
{
printf ( "My find free\n" );
	p_block current = global_base;
	while ( current && !( current->free && (current->size >= size) ) )
	{
		*last = current;
		current = current->next;
	}
//	{ // Mentres current sigui valid, el tamany mes pe
//		*last = current;
//	}
return current;
}

p_block request_space ( p_block last, size_t size )
{
printf ( "Request space\n" );
	p_block block;
	block = sbrk (0);

	if ( sbrk(size) == ENOMEM ) return NULL;
	if ( last ) last->next = block;

	block->size = size;
	block->next = NULL;
	block->free = IS_NOT_FREE;
return block;
}

void *malloc ( size_t size )
{
printf ( "My malloc\n" );
	p_block block, last;
	size += META_SIZE;

	if ( size <= 0 ) return NULL;

	if ( global_base )
	{
		block = find_free_block ( &last, size ); // Definim last
		if ( block ) block->free = IS_NOT_FREE; // Em canviat a block, el important aqui es aquest
		else
		{
			block = request_space ( last, size );
			if ( !block ) return NULL;
		}
	} else
	{ // Primer cas, quan mai s'ha reservat memoria
		block = request_space ( NULL, size );
		if ( !block ) return NULL;
		global_base = block;
	}
return block +1;
}

void *mallocSimple ( size_t size )
{
	void *p = sbrk (0);

	if ( sbrk (size) == ENOMEM )
		return NULL;
return p;
}

void *calloc ( size_t nelem, size_t elsize )
{
	void *ptr;
	size_t size = nelem * elsize;

	ptr = malloc ( size );
	if ( ptr == NULL ) return NULL;

	memset ( (char *)ptr, 0, size );
return ptr;
}

void *realloc ( void *ptr, size_t size )
{
	void *new;
	if ( ptr )
	{ // Controlem el cas null
		p_block block = return_pointer_block ( ptr );
		if ( block->size < size )
		{
			new = malloc ( size );
			memcpy ( new, ptr, block->size );
			block->free = IS_FREE;
			ptr = new;
		}
		return ptr;
	}
return malloc ( size );
}
