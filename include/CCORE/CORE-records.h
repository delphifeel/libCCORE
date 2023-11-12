#ifndef _CORE_RECORDS_H_
#define _CORE_RECORDS_H_

#include "CORE-vector.h"

typedef struct {
    CVector(string) fields;
} CRecord;

CVector_Define(CRecord);
typedef CVector(CRecord) CRecords;

#define CRecords_Free(records_ptr)  do { \
    for (uint i = 0; i < (records_ptr)->size; i++) {                  \
        CVector_Free(&CVector_GetPtr((records_ptr), i)->fields);      \
    }                                                           \
    CVector_Free((records_ptr));                                      \
} while (0)


#define CRecords_GetField(record_ptr, index)  (CVector_Get(&record_ptr->fields, index))
#define CRecords_Get(records_ptr, index)      (CVector_GetPtr(records_ptr, index))

#endif