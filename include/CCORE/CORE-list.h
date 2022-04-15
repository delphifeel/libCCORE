#ifndef _CORE_LIST_H_
#define _CORE_LIST_H_

#include "CORE-types.h"
#include "CORE-object.h"
#include "CORE-list-private.h"

#define CList_ForEach   _CList_ForEach

bool CList_Remove(CList instance, void *value);
void CList_Append(CList instance, void *value);
void CList_Prepend(CList instance, void *value);
bool CList_IsEmpty(CList instance);

void CList_Create(CList *instance_ptr);
void CList_Free(CList *instance_ptr);

#endif
