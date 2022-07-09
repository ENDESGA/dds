# list
 
## usage:
```c
#include "hept.h"

{
  list l = new_list( int );
  list_add( l, int, 7 );
  list_set( l, int, 77, 0 );
  int i = list_get( l, int, 1 ); // 77
  int j = l.size; // 2
}
```
