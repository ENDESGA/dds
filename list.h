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
		uint size_type;
		//
		void* data;
} list;

#define new_list( type ) _new_list( sizeof( type ) )
list _new_list( uint type_size )
{
	list l;
	l.size = 0;
	l.size_mem = 1;
	l.size_type = type_size;
	l.data = malloc( l.size_type );
	return l;
}

uint list_data_fit( list* const in_list )
{
	in_list->size_mem = ( ( in_list->size < in_list->size_mem ) ? ( in_list->size_mem << 1 ) : ( in_list->size + 1 ) );
	in_list->data = realloc( in_list->data, in_list->size_mem * in_list->size_type );
	return in_list->size_mem;
}

#define list_get( l, t, p ) ( (t*)l.data )[ p ]

#define list_add( l, t, v )                                                              \
	do {                                                                                   \
		l.size_mem = ( ( l.size < l.size_mem ) ? ( l.size_mem ) : ( list_data_fit( &l ) ) ); \
		*(t*)&( (t*)( l.data ) )[ l.size++ ] = v;                                            \
	} while( 0 )

#define list_set( l, t, v, p )                                                                              \
	do {                                                                                                         \
		l.size = ( ( p < l.size ) ? ( l.size ) : ( p ) );                                                          \
		l.size_mem = ( ( l.size < l.size_mem ) ? ( l.size_mem ) : ( list_data_fit( &l ) ) );                       \
		memmove( l.data + ( l.size_type * ( p + 1 ) ), l.data + ( l.size_type * ( p ) ), l.size++ * l.size_type ); \
		*(t*)&( (t*)( l.data ) )[ p ] = v;                                                                         \
	} while( 0 )
