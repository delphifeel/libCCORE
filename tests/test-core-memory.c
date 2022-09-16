#include "CCORE.h"

static void TEST_Allocations(void)
{
    // alloc
    int *a = CORE_MemAlloc(sizeof(int), 1);
    *a = 10;
    CORE_AssertIntEqual(*a, 10);

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

    // fre
    CORE_MemFree(b);
    CORE_MemFree(b);
}

int main()
{
    TEST_Allocations();
    return 0;
}