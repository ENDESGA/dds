# list
 
## usage:
```c
#include "hept.h"

{
  list l = new_list( int );
  list_add( l, int, 7 );
  list_add( l, int, 77 );
  int i = ( (int*)l.data )[1]; // 77
  int j = l.size; // 2
}
```
