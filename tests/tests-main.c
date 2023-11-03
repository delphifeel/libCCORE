#include "../include/CCORE.h"

#include "test-core-memory.c"
#include "test-core-vector.c"

int main()
{
    CORE_DebugStdOut("Running libCCORE tests .");
    test_core_memory();
    CORE_DebugStdOut(".");
    test_core_vector();
    CORE_DebugStdOut(". PASS\n");
    return 0;
}