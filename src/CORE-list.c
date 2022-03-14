#include "CCORE/CORE-object.h"
#include "CCORE/CORE-memory.h"
#include "CCORE/CORE-list.h"


static ListNode *_CreateListNode(void *value) 
{
    ListNode *node = CORE_MemAlloc(sizeof(ListNode), 1);
    node->value = value;
    node->next = NULL;
    return node;
}

void CList_Create(CList *instance_ptr)
{
    *instance_ptr = CORE_MemAlloc(sizeof(struct CList), 1);
    CList instance = *instance_ptr;
    instance->head = NULL;
    instance->tail = NULL;
}

void CList_Free(CList *instance_ptr) 
{
    ListNode *iter = (*instance_ptr)->head;
    while (iter != NULL) 
    {
        ListNode *elementToFree = iter;
        iter = iter->next;
        CORE_MemFree(elementToFree);
    }
    CORE_MemFree(*instance_ptr);
}

void CList_Append(CList instance, void *value) 
{
    ListNode *new_node = _CreateListNode(value);
    if (instance->head == NULL) 
    {
        instance->head = new_node;
    }
    
    if (instance->tail != NULL) 
    {
        instance->tail->next = new_node;
    }
    
    instance->tail = new_node;
}

void CList_Prepend(CList instance, void *value) 
{
    ListNode *new_node = _CreateListNode(value);
    if (instance->head != NULL) 
    {
        new_node->next = instance->head;
    }
    
    instance->head = new_node;
    
    if (instance->tail == NULL) 
    {
        instance->tail = new_node;
    }
}

bool CList_IsEmpty(CList instance) 
{
    return (instance->head == NULL) && (instance->tail == NULL);
}
