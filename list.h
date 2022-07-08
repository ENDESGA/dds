#include <memory.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef uint
typedef unsigned int uint;
#endif

typedef struct list_s
{
		uint id;
		uint size;
		uint size_mem;
		uint size_data;
		//
		void* data;
} list;

#define new_list( type ) _new_list( sizeof( type ) )
list _new_list( uint type_size )
{
	list l;
	l.size = 0;
	l.size_mem = 1;
	l.size_data = type_size;
	l.data = malloc( l.size_data );
	return l;
}

#define list_add( l, t, v )                                                              \
	do {                                                                                   \
		l.size_mem = ( ( l.size < l.size_mem ) ? ( l.size_mem ) : ( list_data_fit( &l ) ) ); \
		*(t*)&( (t*)( l.data ) )[ l.size++ ] = v;                                            \
	} while( 0 )

uint list_data_fit( list* const in_list )
{
	in_list->size_mem <<= 1;
	in_list->data = reallocarray( in_list->data, in_list->size_mem, in_list->size_data );
	return in_list->size_mem;
}