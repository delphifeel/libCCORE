#ifndef _CORE_LIST_H_
#define _CORE_LIST_H_

#include "CORE-types.h"
#include "CORE-object.h"
#include "CORE-list-private.h"

#define CList_ForEach   _CList_ForEach

bool CList_Remove(CList *list, void *value);
void CList_Append(CList *list, void *value);
void CList_Prepend(CList *list, void *value);
bool CList_IsEmpty(const CList *list);

CList *CList_Create(void);
void CList_Free(CList **list_ptr);

#endif
