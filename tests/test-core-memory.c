#include "CCORE.h"

void test_core_memory(void)
{
    // alloc
    int *a = CORE_MemAlloc(sizeof(int), 1);
    *a = 10;
    CORE_AssertIntEqual(*a, 10);
    CORE_MemFree(a);

    // calloc
    int *b = CORE_MemCalloc(sizeof(int), 3);
    b[0] = 22;
    b[1] = 33;
    CORE_AssertIntEqual(b[0], 22);
    CORE_AssertIntEqual(b[1], 33);

    // realloc
    b = CORE_MemRealloc(b, sizeof(int), 1);
    b[0] = 66;
    CORE_AssertIntEqual(b[0], 66);

    // free
    CORE_MemFree(b);
}