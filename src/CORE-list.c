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

CList *CList_Create(void)
{
    CList *list = CORE_MemAlloc(sizeof(CList), 1);
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void CList_Free(CList **list_ptr) 
{
    ListNode *iter = (*list_ptr)->head;
    ListNode *element_to_free = NULL;
    while (iter != NULL) 
    {
        element_to_free = iter;
        iter = iter->next;
        CORE_MemFree(element_to_free);
    }
    CORE_MemFree(*list_ptr);
}

bool CList_Remove(CList *list, void *value)
{
    CORE_AssertPointer(value);

    if (CList_IsEmpty(list)) {
        return false;
    }

    ListNode *iter = list->head;
    ListNode *prev_iter = NULL;
    while (iter != NULL) 
    {
        if (iter->value != value) {
            prev_iter = iter;
            iter = iter->next;
            continue;
        }
        
        if (iter == list->head) {
            list->head = iter->next;
        }
        if (iter == list->tail) {
            list->tail = prev_iter;
        }
        if (prev_iter != NULL) {
            prev_iter->next = iter->next;
        }

        CORE_MemFree(iter);
        return true;
    }

    return false;
}

void CList_Append(CList *list, void *value) 
{
    ListNode *new_node = _CreateListNode(value);
    if (list->head == NULL) {
        list->head = new_node;
    }
    
    if (list->tail != NULL) {
        list->tail->next = new_node;
    }
    
    list->tail = new_node;
}

void CList_Prepend(CList *list, void *value) 
{
    ListNode *new_node = _CreateListNode(value);
    new_node->next = list->head;
    list->head = new_node;
    
    if (list->tail == NULL) {
        list->tail = new_node;
    }
}

bool CList_IsEmpty(const CList *list) 
{
    return (list->head == NULL) && (list->tail == NULL);
}
