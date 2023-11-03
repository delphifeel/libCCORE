CVector_Define(int);

void test_core_vector(void)
{
    // init vector
    CVector(int) v;
    CVector_Init(&v, 0);

    // push
    CVector_Push(&v, 33);
    
    // get by ptr
    uint *a = CVector_GetPtr(&v, 0);
    *a = 666;
    CORE_AssertIntEqual(CVector_Pop(&v), 666);

    // free memory
    CVector_Free(&v);
}