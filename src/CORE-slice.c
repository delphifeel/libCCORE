#include "CCORE/CORE-debug.h"
#include "CCORE/CORE-memory.h"
#include "CCORE/CORE-slice.h"

CSlice *CSlice_CreateFromArray(
                            void    *array[], 
                            uint    array_size, 
                            uint    from_index, 
                            uint    to_index)
{
    CSlice *slice = CORE_MemAlloc(sizeof(CSlice), 1);

    slice->src_array = array;
    slice->src_array_alloced = false;
    slice->start_index = from_index == CSLICE_FROM_START ? 0 : from_index;
    uint endIndex = to_index == CSLICE_TO_THE_END ? array_size : to_index;
    slice->len = endIndex - slice->start_index;
    slice->cap = array_size - slice->start_index;
    return slice;
}

CSlice *CSlice_CreateFromSlice(CSlice *src_slice, uint from_index, uint to_index)
{
    uint start_index = src_slice->start_index + (from_index == CSLICE_FROM_START ? 0 : from_index);
    uint end_index = src_slice->start_index + 
                    (to_index == CSLICE_TO_THE_END ? src_slice->len : to_index);
    uint array_size = src_slice->start_index + src_slice->cap;
    
    return CSlice_CreateFromArray(src_slice->src_array, array_size, start_index, end_index);
}

void CSlice_Append(CSlice *slice, const void *value)
{
    CORE_AssertWithMessage(
        slice->src_array_alloced, 
        "Can't append to slice created from array or other slice\n"
    );

    if (slice->len == slice->cap) {
        uint new_cap = slice->cap * 2 + 1;
        uint new_arr_size = slice->start_index + new_cap;
        slice->src_array = CORE_MemRealloc(slice->src_array, sizeof(void*), new_arr_size);
        slice->cap = new_cap;
    }
    
    slice->len++;
    void **element_ptr = _CSlice_ElementPtrByIndex(slice, slice->len - 1);
    CORE_MemCpy(element_ptr, &value, sizeof(value));
}

uint CSlice_Size(const CSlice *slice) 
{
    return slice->len;
}

uint CSlice_Cap(const CSlice *slice) 
{
    return slice->cap;
}

CSlice *CSlice_Create(uint default_cap) 
{
    CSlice *slice = CORE_MemAlloc(sizeof(CSlice), 1);
    slice->src_array = CORE_MemAlloc(sizeof(void*), default_cap);

    slice->src_array_alloced = true;
    slice->start_index = 0;
    slice->len = 0;
    slice->cap = default_cap;
    return slice;
}

void CSlice_Free(CSlice **slice_ptr) 
{
    CSlice *slice = *slice_ptr;
    if (slice->src_array_alloced) {
       CORE_MemFree(slice->src_array);
    }
    CORE_MemFree(slice);
}