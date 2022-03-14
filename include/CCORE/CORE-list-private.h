#ifndef _CORE_LIST_PRIVATE_H_
#define _CORE_LIST_PRIVATE_H_

#include "CCORE/CORE-object.h"


typedef struct ListNode
{
    void            *value;
    struct ListNode *next;
} ListNode;

typedef struct CList
{
    ListNode *head;
    ListNode *tail;
} *CList;

#define _CList_ForEach(CLIST, ITEM)                                                         \
    ListNode    *ITEM##_iter;                                                               \
    for (ITEM##_iter = CLIST->head, ITEM = ITEM##_iter ? ITEM##_iter->value : NULL;         \
         ITEM##_iter != NULL;                                                               \
         ITEM##_iter = ITEM##_iter->next, ITEM = ITEM##_iter ? ITEM##_iter->value : NULL)

#endif