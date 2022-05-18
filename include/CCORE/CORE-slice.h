#ifndef _CORE_SLICE_H_
#define _CORE_SLICE_H_

#include "CORE-types.h"
#include "CORE-slice-private.h"

#define CSLICE_FROM_START 		    (0)
#define CSLICE_TO_THE_END 		    (0)

typedef struct CSlice_s CSlice;

CSlice *CSlice_Create(uint default_cap);
void CSlice_Free(CSlice **slice_ptr);
CSlice *CSlice_CreateFromArray(void *array[], uint array_size, uint from_index, uint to_index);
CSlice *CSlice_CreateFromSlice(CSlice *src_slice, uint from_index, uint to_index);
void CSlice_FreeAllElements(CSlice *slice);
void CSlice_Append(CSlice *slice, const void *value);
uint CSlice_Size(const CSlice *slice);
uint CSlice_Cap(const CSlice *slice);

#define CSlice_Get          _CSlice_Get
#define CSlice_Pop          _CSlice_Pop

#endif
