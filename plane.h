/*

	dds :: dynamic data structures

	plane: automatically expands when data is set beyond 2D positive&negative-bounds

*/

#ifndef dds_plane
#define dds_plane

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

typedef struct _plane_struct
{
		uint width_11, width_10, width_00, width_01;
		uint height_11, height_10, height_00, height_01;
		uint area_11, area_10, area_00, area_01;
		uint count_11, count_10, count_00, count_01;
		uint size_mem_11, size_mem_10, size_mem_00, size_mem_01;
		uint size_type;
		//
		dataptr data_11;
		dataptr data_10;
		dataptr data_00;
		dataptr data_01;
} plane;

#define new_plane( type ) _new_plane( sizeof( type ) )
plane _new_plane( uint type_size )
{
	plane p;
	p.width_11 = 0, p.width_10 = 0, p.width_00 = 0, p.width_01 = 0;
	p.height_11 = 0, p.height_10 = 0, p.height_00 = 0, p.height_01 = 0;
	p.count_11 = 0, p.count_10 = 0, p.count_00 = 0, p.count_01 = 0;
	p.size_mem_11 = 1, p.size_mem_10 = 1, p.size_mem_00 = 1, p.size_mem_01 = 1;
	p.size_type = type_size;
	//
	p.data_11 = (dataptr)malloc( p.size_type);
	p.data_10 = (dataptr)malloc( p.size_type);
	p.data_00 = (dataptr)malloc( p.size_type);
	p.data_01 = (dataptr)malloc( p.size_type);
	return p;
}

// param importance:
// p - plane
// t - type
// v - value
// x - horizonal position
// y - vertical position

#define plane_get( p, t, x, y ) ( ( x >= 0 ) ? ( ( y >= 0 ) ? ( ( (tile*)p.data_11 )[ ( x ) + ( y * p.width_11 ) ] ) : ( ( (tile*)p.data_10 )[ ( x ) + ( ( -y - 1 ) * p.width_10 ) ] ) ) : ( ( y < 0 ) ? ( ( (tile*)p.data_00 )[ ( -x - 1 ) + ( ( -y - 1 ) * p.width_00 ) ] ) : ( ( (tile*)p.data_01 )[ ( -x - 1 ) + ( (y)*p.width_01 ) ] ) ) )

//

#define plane_set( p, t, v, x, y )                                                                     \
	do {                                                                                                 \
		if( x >= 0 )                                                                                       \
		{                                                                                                  \
			if( y >= 0 )                                                                                     \
			{                                                                                                \
				p.width_11 = ( ( x < p.width_11 ) ? ( p.width_11 ) : ( x + 1 ) );                              \
				p.height_11 = ( ( y < p.height_11 ) ? ( p.height_11 ) : ( y + 1 ) );                           \
				p.area_11 = p.width_11 * p.height_11;                                                          \
				p.count_11++;                                                                                  \
                                                                                                       \
				if( p.area_11 >= p.size_mem_11 )                                                               \
				{                                                                                              \
					p.size_mem_11 = ( ( p.area_11 == p.size_mem_11 ) ? ( p.size_mem_11 << 1 ) : ( p.area_11 ) ); \
					p.data_11 = (dataptr)realloc( p.data_11, p.size_mem_11 * p.size_type );                      \
				}                                                                                              \
				( (t*)( p.data_11 ) )[ ( x ) + ( y * p.width_11 ) ] = v;                                       \
			} else                                                                                           \
			{                                                                                                \
				p.width_10 = ( ( x < p.width_10 ) ? ( p.width_10 ) : ( x + 1 ) );                              \
				p.height_10 = ( ( y < p.height_10 ) ? ( p.height_10 ) : ( -y ) );                              \
				p.area_10 = p.width_10 * p.height_10;                                                          \
				p.count_10++;                                                                                  \
                                                                                                       \
				if( p.area_10 >= p.size_mem_10 )                                                               \
				{                                                                                              \
					p.size_mem_10 = ( ( p.area_10 == p.size_mem_10 ) ? ( p.size_mem_10 << 1 ) : ( p.area_10 ) ); \
					p.data_10 = (dataptr)realloc( p.data_10, p.size_mem_10 * p.size_type );                      \
				}                                                                                              \
				( (t*)( p.data_10 ) )[ ( x ) + ( ( -y - 1 ) * p.width_10 ) ] = v;                              \
			}                                                                                                \
		} else                                                                                             \
		{                                                                                                  \
			if( y < 0 )                                                                                      \
			{                                                                                                \
				p.width_00 = ( ( ( -x - 1 ) < p.width_00 ) ? ( p.width_00 ) : ( -x ) );                        \
				p.height_00 = ( ( ( -y - 1 ) < p.height_00 ) ? ( p.height_00 ) : ( -y ) );                     \
				p.area_00 = p.width_00 * p.height_00;                                                          \
				p.count_00++;                                                                                  \
                                                                                                       \
				if( p.area_00 >= p.size_mem_00 )                                                               \
				{                                                                                              \
					p.size_mem_00 = ( ( p.area_00 == p.size_mem_00 ) ? ( p.size_mem_00 << 1 ) : ( p.area_00 ) ); \
					p.data_00 = (dataptr)realloc( p.data_00, p.size_mem_00 * p.size_type );                      \
				}                                                                                              \
				( (t*)( p.data_00 ) )[ ( ( -x - 1 ) ) + ( ( -y - 1 ) * p.width_00 ) ] = v;                     \
			} else                                                                                           \
			{                                                                                                \
				p.width_01 = ( ( ( -x - 1 ) < p.width_01 ) ? ( p.width_01 ) : ( -x ) );                        \
				p.height_01 = ( ( y < p.height_01 ) ? ( p.height_01 ) : ( y + 1 ) );                           \
				p.area_01 = p.width_01 * p.height_01;                                                          \
				p.count_01++;                                                                                  \
                                                                                                       \
				if( p.area_01 >= p.size_mem_00 )                                                               \
				{                                                                                              \
					p.size_mem_01 = ( ( p.area_01 == p.size_mem_00 ) ? ( p.size_mem_00 << 1 ) : ( p.area_01 ) ); \
					p.data_01 = (dataptr)realloc( p.data_01, p.size_mem_01 * p.size_type );                      \
				}                                                                                              \
				( (t*)( p.data_01 ) )[ ( ( -x - 1 ) ) + ( y * p.width_01 ) ] = v;                              \
			}                                                                                                \
		}                                                                                                  \
	} while( 0 )

//

#endif
