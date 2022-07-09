# list
 
## usage:
```c
#include "hept.h"

{
  list l = new_list( int );
  list_add( l, int, 7 );
  list_set( l, int, 77, 7 ); // can set beyond alloc
  int i = list_get( l, int, 1 ); // uninit memory
  int j = l.size; // 2
}
```
