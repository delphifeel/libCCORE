#include "CCORE.h"


void test_core_vector(void)
{
    // define type
    CVector_Define(int);

    // init vector
    CVector(uint) v;
    CVector_Init(&v, 0);

    // push
    CVector_Push(&v, 33);
    
    // get by ptr, get
    uint *a = CVector_GetPtr(&v, 0);
    *a = 666;
    uint value = CVector_Get(&v, 0);
    CORE_AssertIntEqual(value, 666);

    // pop
    value = CVector_Pop(&v);
    CORE_AssertIntEqual(value, 666);
    CORE_Assert(v.size == 0);

    // free memory
    CVector_Free(&v);

    // for loop with structs
    typedef struct { uint age; uint height; } Man;
    CVector_Define(Man);
    CVector(Man) man_list;
    CVector_Init(&man_list, 0);

    Man old_man = {70, 160};
    CVector_Push(&man_list, old_man);

    Man young_man = {15, 166};
    CVector_Push(&man_list, young_man);

    Man *man_ptr = NULL;
    for (uint i = 0; i < man_list.size; i++) {
        switch (i)
        {
        case 0:
            man_ptr = CVector_GetPtr(&man_list, 0);
            CORE_Assert(man_ptr->age == old_man.age);
            break;
        case 1:
            man_ptr = CVector_GetPtr(&man_list, 1);
            CORE_Assert(man_ptr->age == young_man.age);
            break;
        }
    }

    CVector_Free(&man_list);
}