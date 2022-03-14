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

#define CORE_MemCpy                                 memcpy
#define CORE_MemEqual(PTR1, PTR2, SIZE)             (memcmp(PTR1, PTR2, SIZE) == 0)

#define CORE_MemNewCopy(DEST, SRC, SRC_SIZE)   do {     \
    DEST = CORE_MemAlloc(SRC_SIZE, 1);                  \
    CORE_MemCpy(DEST, SRC, SRC_SIZE);                   \
} while (0)

#endif
