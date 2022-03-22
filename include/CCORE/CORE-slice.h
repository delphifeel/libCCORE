#ifndef _CORE_SLICE_H_
#define _CORE_SLICE_H_

#include "CORE-types.h"
#include "CORE-slice-private.h"

#define CSLICE_FROM_START 		    (0)
#define CSLICE_TO_THE_END 		    (0)

typedef struct CSlice *CSlice;

void CSlice_Create(CSlice *slice_ptr, uint default_cap);
void CSlice_Free(CSlice *slice_ptr);
void CSlice_CreateFromArray(CSlice *slice_ptr, void *array[], uint array_size, uint from_index, uint to_index);
void CSlice_CreateFromSlice(CSlice *slice_ptr, CSlice src_slice, uint from_index, uint to_index);
void CSlice_FreeAllElements(CSlice slice);
void CSlice_Append(CSlice slice, const void *value);
uint CSlice_Size(CSlice slice);
uint CSlice_Cap(CSlice slice);

#define CSlice_Get          _CSlice_Get
#define CSlice_Pop          _CSlice_Pop

#endif
