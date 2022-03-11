#ifndef _CORE_MEMORY_H_
#define _CORE_MEMORY_H_

#include <stdlib.h>
#include <string.h>

#define CORE_MemAlloc(SIZE, COUNT)				    malloc((SIZE) * (COUNT))
#define CORE_MemCalloc(SIZE, COUNT)			        calloc((COUNT), (SIZE))
#define CORE_MemRealloc(PTR, SIZE, COUNT)           realloc((PTR), (SIZE) * (COUNT))
#define CORE_MemFree 				                free
#define CORE_MemSet 				                memset
#define CORE_MemZero(PTR, SIZE)		                CORE_MemSet(PTR, 0, SIZE)

#endif
