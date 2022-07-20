/*

dds :: dynamic data structures

grid: automatically expands when data is set beyond 2D positive-bounds

*/

#ifndef dds_grid
#define dds_grid

#include <memory.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef uint
	#define uint unsigned int
#endif

#ifndef dataptr
	#define dataptr unsigned char*
#endif

typedef struct _grid_struct
{
		uint width, height;
		uint area;
		uint count;
		uint size_mem;
		uint size_type;
		//
		dataptr data;
} grid;

#define new_grid( type ) _new_grid( sizeof( type ) )
grid _new_grid( uint type_size )
{
	grid g;
	g.width = 0, g.height = 0;
	g.area = 0;
	g.count = 0;
	g.size_mem = 1;
	g.size_type = type_size;
	//
	g.data = (dataptr)malloc( g.size_type );
	return g;
}

// param importance:
// g - grid
// t - type
// v - value
// x - horizonal position
// y - vertical position

#define _grid_scale( g )                                                          \
	if( g.area >= g.size_mem )                                                      \
	{                                                                               \
		g.size_mem = ( ( g.area == g.size_mem ) ? ( g.size_mem << 1 ) : ( g.area ) ); \
		g.data = (dataptr)realloc( g.data, g.size_mem * g.size_type );                \
	}

#define _grid_apply( g, t, v, x, y ) ( (t*)( g.data ) )[ ( x ) + ( y * g.width ) ] = v

//

#define grid_set( g, t, v, x, y )                               \
	do {                                                          \
		g.width = ( ( x < g.width ) ? ( g.width ) : ( x + 1 ) );    \
		g.height = ( ( y < g.height ) ? ( g.height ) : ( y + 1 ) ); \
		g.area = g.width * g.height;                                \
		g.count++;                                                  \
                                                                \
		_grid_scale( g );                                           \
		_grid_apply( g, t, v, x, y );                               \
	} while( 0 )

#define grid_delete( g, x, y )                                                                                      \
	do {                                                                                                              \
		memmove( g.data + ( p * g.size_type ), g.data + ( ( p + 1 ) * g.size_type ), ( g.count-- - p ) * g.size_type ); \
	} while( 0 )

//

#endif