#ifndef _CORE_MEMORY_H_
#define _CORE_MEMORY_H_

#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "CORE-debug.h"
#include "CORE-types.h"


void *CORE_MemAllocImpl(size_t size, size_t count, const char *file, uint line);
void *CORE_MemCallocImpl(size_t size, size_t count, const char *file, uint line);
void *CORE_MemReallocImpl(void *ptr, size_t size, size_t count, const char *file, uint line);
void CORE_FreeImpl(void *ptr, const char *file, uint line);


#define CORE_MemAlloc(SIZE, COUNT)				    CORE_MemAllocImpl(SIZE, COUNT, __FILE__, __LINE__)
#define CORE_MemCalloc(SIZE, COUNT)			        CORE_MemCallocImpl(SIZE, COUNT, __FILE__, __LINE__)
#define CORE_MemRealloc(PTR, SIZE, COUNT)           CORE_MemReallocImpl(PTR, SIZE, COUNT, __FILE__, __LINE__)
#define CORE_MemFree(PTR) 				            CORE_FreeImpl(PTR, __FILE__, __LINE__)
#define CORE_MemSet 				                memset
#define CORE_MemZero(PTR, SIZE)		                CORE_MemSet(PTR, 0, SIZE)

#define CORE_MemCpy                                 memcpy
#define CORE_MemCmp(A, B, SIZE)                     (memcmp(A, B, SIZE) == 0)
#define CORE_MemEqual(PTR1, PTR2, SIZE)             (memcmp(PTR1, PTR2, SIZE) == 0)

#define CORE_MemNewCopy(DEST, SRC, SRC_SIZE)   do {     \
    DEST = CORE_MemAlloc(SRC_SIZE, 1);                  \
    CORE_MemCpy(DEST, SRC, SRC_SIZE);                   \
} while (0)

#endif
