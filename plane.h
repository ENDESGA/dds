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
	p.data_11 = (dataptr)calloc( 1, p.size_type );
	p.data_10 = (dataptr)calloc( 1, p.size_type );
	p.data_00 = (dataptr)calloc( 1, p.size_type );
	p.data_01 = (dataptr)calloc( 1, p.size_type );

	return p;
}

// param importance:
// p - plane
// t - type
// v - value
// x - horizonal position
// y - vertical position

#define plane_at( p, t, x, y ) ( ( x >= 0 ) ?                                                                 \
																	 ( ( y >= 0 ) ?                                                             \
																			 ( ( (tile*)p.data_11 )[ ( x ) + ( y * p.width_11 ) ] ) :               \
																			 ( ( (tile*)p.data_10 )[ ( x ) + ( ( -y - 1 ) * p.width_10 ) ] ) ) :    \
																	 ( ( y < 0 ) ?                                                              \
																			 ( ( (tile*)p.data_00 )[ ( -x - 1 ) + ( ( -y - 1 ) * p.width_00 ) ] ) : \
																			 ( ( (tile*)p.data_01 )[ ( -x - 1 ) + ( y * p.width_01 ) ] ) ) )

#define plane_get( p, t, x, y ) ( ( x >= 0 ) ?                                                                       \
																		( ( y >= 0 ) ?                                                                   \
																				( ( x >= p.width_11 || y >= p.height_11 ) ?                                  \
																						( ( t ){ 0 } ) :                                                         \
																						( ( (tile*)p.data_11 )[ ( x ) + ( y * p.width_11 ) ] ) ) :               \
																				( ( x >= p.width_10 || ( -y - 1 ) >= p.height_10 ) ?                         \
																						( ( t ){ 0 } ) :                                                         \
																						( ( (tile*)p.data_10 )[ ( x ) + ( ( -y - 1 ) * p.width_10 ) ] ) ) ) :    \
																		( ( y < 0 ) ?                                                                    \
																				( ( ( -x - 1 ) >= p.width_00 || ( -y - 1 ) >= p.height_00 ) ?                \
																						( ( t ){ 0 } ) :                                                         \
																						( ( (tile*)p.data_00 )[ ( -x - 1 ) + ( ( -y - 1 ) * p.width_00 ) ] ) ) : \
																				( ( ( -x - 1 ) >= p.width_01 || y >= p.height_01 ) ?                         \
																						( ( t ){ 0 } ) :                                                         \
																						( ( (tile*)p.data_01 )[ ( -x - 1 ) + ( y * p.width_01 ) ] ) ) ) )

//

#define _plane_apply( p, t, v, x, y, plane_id )                                                                                                                                                                \
	do {                                                                                                                                                                                                         \
		int __X = ( x ), __Y = ( y );                                                                                                                                                                              \
		uint temp_width_##plane_id = p.width_##plane_id, temp_height_##plane_id = p.height_##plane_id;                                                                                                             \
		p.width_##plane_id = ( ( __X < p.width_##plane_id ) ? ( p.width_##plane_id ) : ( __X + 1 ) );                                                                                                              \
		p.height_##plane_id = ( ( __Y < p.height_##plane_id ) ? ( p.height_##plane_id ) : ( __Y + 1 ) );                                                                                                           \
		p.area_##plane_id = p.width_##plane_id * p.height_##plane_id;                                                                                                                                              \
		p.count_##plane_id++;                                                                                                                                                                                      \
                                                                                                                                                                                                               \
		if( p.area_##plane_id > p.size_mem_##plane_id )                                                                                                                                                            \
		{                                                                                                                                                                                                          \
			p.size_mem_##plane_id = p.area_##plane_id;                                                                                                                                                               \
			dataptr temp_data_##plane_id = (dataptr)calloc( p.size_mem_##plane_id, p.size_type );                                                                                                                    \
			for( uint m_##plane_id = 0; m_##plane_id < temp_height_##plane_id; ++m_##plane_id )                                                                                                                      \
			{                                                                                                                                                                                                        \
				memcpy( temp_data_##plane_id + ( p.width_##plane_id * m_##plane_id * p.size_type ), p.data_##plane_id + ( temp_width_##plane_id * m_##plane_id * p.size_type ), temp_width_##plane_id * p.size_type ); \
			}                                                                                                                                                                                                        \
			p.data_##plane_id = temp_data_##plane_id;                                                                                                                                                                \
		}                                                                                                                                                                                                          \
		( (t*)( p.data_##plane_id ) )[ __X + ( __Y * p.width_##plane_id ) ] = v;                                                                                                                                   \
	} while( 0 )

#define plane_set( p, t, v, x, y )                     \
	do {                                                 \
		int _X = ( x ), _Y = ( y );                        \
		if( ( _X ) >= 0 )                                  \
		{                                                  \
			if( ( _Y ) >= 0 )                                \
			{                                                \
				_plane_apply( p, t, v, _X, _Y, 11 );           \
			} else                                           \
			{                                                \
				_plane_apply( p, t, v, _X, -_Y - 1, 10 );      \
			}                                                \
		} else                                             \
		{                                                  \
			if( ( _Y ) < 0 )                                 \
			{                                                \
				_plane_apply( p, t, v, -_X - 1, -_Y - 1, 00 ); \
			} else                                           \
			{                                                \
				_plane_apply( p, t, v, -_X - 1, _Y, 01 );      \
			}                                                \
		}                                                  \
	} while( 0 )

//

#endif
