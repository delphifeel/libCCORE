#include "CCORE/CORE-memory.h"

#define _CALL_ALLOCATION_FUNC(func_code)                                        \
    void *result = (func_code);                                                 \
    CORE_AssertWithMessageEx(file, line, result != NULL, "Out of memory\n");    \
    return result;

void *CORE_MemAllocImpl(size_t size, size_t count, const char *file, uint line)
{
    _CALL_ALLOCATION_FUNC(
        malloc(size * count)
    );
}

void *CORE_MemCallocImpl(size_t size, size_t count, const char *file, uint line)
{
    _CALL_ALLOCATION_FUNC(
        calloc(count, size)
    );
}

void *CORE_MemReallocImpl(void *ptr, size_t size, size_t count, const char *file, uint line)
{
    _CALL_ALLOCATION_FUNC(
        realloc(ptr, size * count)
    );
}

void CORE_FreeImpl(void *ptr, const char *file, uint line)
{
    CORE_AssertWithMessageEx(file, line, ptr != NULL, "Null pointer exception\n");
    free(ptr);
}