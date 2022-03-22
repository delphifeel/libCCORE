#ifndef _CORE_SLICE_PRIVATE_H_
#define _CORE_SLICE_PRIVATE_H_


#include "CORE-memory.h"


struct CSlice 
{
    void        **src_array;
    uint        start_index;
    uint        len;
    uint        cap;
};

#define _CSlice_ElementPtrByIndex(slice, index)                             \
    (CORE_AssertWithMessage(index < slice->len, "Index out of bounds\n"),   \
    slice->src_array + slice->start_index + index)

#define _CSlice_Get(slice, index)                                            \
    (*_CSlice_ElementPtrByIndex(slice, index))

#define _CSlice_Pop(slice)                                                   \
    (CORE_AssertWithMessage(slice->len > 0, "Index out of bounds\n"),        \
     slice->len--,                                                           \
     *(slice->src_array + slice->start_index + slice->len))


#endif