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

// param importance:
// l - list
// t - type
// v - value
// p - position

#define list_get( l, t, p ) ( (t*)l.data )[ p ]
#define list_1st( l, t ) ( (t*)l.data )[ 0 ]
#define list_2nd( l, t ) ( (t*)l.data )[ 1 ]
#define list_3rd( l, t ) ( (t*)l.data )[ 2 ]
#define list_end( l, t ) ( (t*)l.data )[ l.size - 1 ]

#define _list_scale_mem( l )                                                      \
	if( l.size >= l.size_mem )                                                      \
	{                                                                               \
		l.size_mem = ( ( l.size == l.size_mem ) ? ( l.size_mem << 1 ) : ( l.size ) ); \
		l.data = realloc( l.data, l.size_mem * l.size_type );                         \
	}

#define _list_scale( l, p )                             \
	l.size = ( ( p < l.size ) ? ( l.size ) : ( p + 1 ) ); \
	_list_scale_mem( l );

#define _list_apply( l, t, v, p ) *(t*)&( (t*)( l.data ) )[ p ] = v

//

#define list_add( l, t, v )           \
	do {                                \
		_list_scale_mem( l );             \
		_list_apply( l, t, v, l.size++ ); \
	} while( 0 )

#define list_set( l, t, v, p ) \
	do {                         \
		_list_scale( l, p );       \
		_list_apply( l, t, v, p ); \
	} while( 0 )

#define list_insert( l, t, v, p )                                                                                      \
	do {                                                                                                                 \
		if( p < l.size )                                                                                                   \
		{                                                                                                                  \
			_list_scale( l, l.size );                                                                                        \
			memmove( l.data + ( l.size_type * ( p + 1 ) ), l.data + ( l.size_type * ( p ) ), ( l.size - p ) * l.size_type ); \
		} else                                                                                                             \
		{                                                                                                                  \
			_list_scale( l, p );                                                                                             \
		}                                                                                                                  \
		_list_apply( l, t, v, p );                                                                                         \
	} while( 0 )
