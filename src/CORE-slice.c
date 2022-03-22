#include "CCORE/CORE-debug.h"
#include "CCORE/CORE-memory.h"
#include "CCORE/CORE-slice.h"

void CSlice_CreateFromArray(CSlice  *slice_ptr, 
                            void    *array[], 
                            uint    array_size, 
                            uint    from_index, 
                            uint    to_index)
{
    *slice_ptr = CORE_MemAlloc(sizeof(struct CSlice), 1);
    CSlice slice = *slice_ptr;

    slice->src_array = array;
    slice->start_index = from_index == CSLICE_FROM_START ? 0 : from_index;
    uint endIndex = to_index == CSLICE_TO_THE_END ? array_size : to_index;
    slice->len = endIndex - slice->start_index;
    slice->cap = array_size - slice->start_index;
}

void CSlice_CreateFromSlice(CSlice *slice_ptr, CSlice src_slice, uint from_index, uint to_index)
{
    uint start_index = src_slice->start_index + (from_index == CSLICE_FROM_START ? 0 : from_index);
    uint end_index = src_slice->start_index + 
                    (to_index == CSLICE_TO_THE_END ? src_slice->len : to_index);
    uint array_size = src_slice->start_index + src_slice->cap;
    
    CSlice_CreateFromArray(slice_ptr, src_slice->src_array, array_size, start_index, end_index);
}

void CSlice_Append(CSlice slice, const void *value)
{
    if (slice->len == slice->cap) 
    {
        uint new_cap = slice->cap * 2 + 1;
        uint new_arr_size = slice->start_index + new_cap;
        slice->src_array = CORE_MemRealloc(slice->src_array, sizeof(void*), new_arr_size);
        slice->cap = new_cap;
    }
    
    slice->len++;
    void **elementPtr = _CSlice_ElementPtrByIndex(slice, slice->len - 1);
    CORE_MemCpy(elementPtr, &value, sizeof(value));
}

uint CSlice_Size(CSlice slice) 
{
    return slice->len;
}

uint CSlice_Cap(CSlice slice) 
{
    return slice->cap;
}

void CSlice_Create(CSlice *slice_ptr, uint default_cap) 
{
    *slice_ptr = CORE_MemAlloc(sizeof(struct CSlice), 1);
    CSlice slice = *slice_ptr;
    slice->src_array = CORE_MemAlloc(sizeof(void*), default_cap);
    slice->start_index = 0;
    slice->len = 0;
    slice->cap = default_cap;
}

void CSlice_Free(CSlice *slice_ptr) 
{
    CSlice slice = *slice_ptr;
    CORE_MemFree(slice->src_array);
    CORE_MemFree(slice);
}