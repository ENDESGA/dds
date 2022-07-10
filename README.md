# dds :: *dynamic data structures*

# list:
1D data structure which automatically expands to fit data placed in any position.

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
  int i = list_get( l, int, 1 ); // uninit memory
  int j = l.size; // 2
}
```
