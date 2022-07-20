# dds :: *dynamic data structures*

# list:
1D data structure which automatically expands to fit data placed in any ***positive*** position.

```c
list_add( list, type, value ); // pushes the value to the end of the list
list_get( list, type, position ); // get the value at position in list
list_set( list, type, value, position ); // set the value at position in list
list_insert( list, type, value, position ); // insert the value at position in list
```

### usage:
```c
{
  list l = new_list( int );
  list_add( l, int, 7 );
  list_set( l, int, 77, 7 ); // can set beyond alloc
  int i = list_get( l, int, 1 ); // uninit mem : returns 0
  int j = l.size; // 2
}
```
-------
# grid:
2D data structure which automatically expands to fit data placed in any ***positive*** position.

```c
grid_get( list, type, x_position, y_position ); // get the value at x,y position in grid
grid_set( list, type, value, x_position, y_position ); // set the value at x,y position in grid
```

### usage:
```c
{
  grid g = new_grid( int );
  grid_set( l, int, 77, 0, 1 ); // set 0,1 to 77
  int i = grid_get( l, int, 1, 1 ); // uninit mem : returns 0
  int j = g.width; // 1
  int k = g.height; // 2
}
```
-------
# plane:
2D data structure which automatically expands to fit data placed in any ***negative or positive*** position.

```c
plane_get( list, type, x_position, y_position ); // get the value at x,y position in plane
plane_set( list, type, value, x_position, y_position ); // set the value at x,y position in plane
```

### usage:
```c
{
  plane p = new_plane( int );
  plane_set( p, int, 7, -3, -27); // set -3,-27 to 7
  int i = plane_get(p, int, -3, -27); // returns 7
}
```
