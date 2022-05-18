#ifndef _CORE_OBJECT_PRIVATE_H_
#define _CORE_OBJECT_PRIVATE_H_

#include "CORE-memory.h"
#include "CORE-debug.h"

#define _CORE_OBJECT_CREATE(OBJECT_PTR, TYPE)   do {                            \
    CORE_AssertPointer(OBJECT_PTR);                                             \
    *(OBJECT_PTR) = CORE_MemAlloc(sizeof(struct TYPE##_STRUCT), 1);             \
} while (0)                                                                     


#define _CORE_OBJECT_FREE(OBJECT_PTR)    do {        \
    CORE_AssertPointer(OBJECT_PTR);                 \
    CORE_MemFree(*(OBJECT_PTR));                    \
    *(OBJECT_PTR) = NULL;                           \
} while (0)                                         


#endif