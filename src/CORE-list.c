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
    ListNode *elementToFree = NULL;
    while (iter != NULL) 
    {
        elementToFree = iter;
        iter = iter->next;
        CORE_MemFree(elementToFree);
    }
    CORE_MemFree(*instance_ptr);
}

bool CList_Remove(CList instance, void *value)
{
    CORE_AssertPointer(value);

    if (CList_IsEmpty(instance)) {
        return false;
    }

    ListNode *iter = instance->head;
    ListNode *prev_iter = NULL;
    while (iter != NULL) 
    {
        if (iter->value != value) {
            prev_iter = iter;
            iter = iter->next;
            continue;
        }
        
        if (iter == instance->head) {
            instance->head = iter->next;
        }
        if (iter == instance->tail) {
            instance->tail = prev_iter;
        }
        if (prev_iter != NULL) {
            prev_iter->next = iter->next;
        }

        CORE_MemFree(iter);
        return true;
    }

    return false;
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
    new_node->next = instance->head;
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
