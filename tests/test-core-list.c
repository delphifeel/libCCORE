#include "CCORE.h"

void TEST_List_Create() 
{
	CList list;


	CList_Create(&list);

	CORE_Assert(list != NULL);	
	CORE_Assert(list->head == NULL);
	CORE_Assert(list->tail == NULL);

	CList_Free(&list);
}

void TEST_List_Append() {
	CList list;


	CList_Create(&list);

	// if first node - head and tail the same
	int first_value = 333;
	CList_Append(list, &first_value);

	CORE_Assert(list->head == list->tail);

	// if second node - head old, tail is new 
	int second_value = 666;
	CList_Append(list, &second_value);

	CORE_Assert(
			(list->head != list->tail) &&
			(list->head->value == &first_value) &&
			(list->tail->value == &second_value)
	);

	// if third node and so on - same behavior as with second node
	int third_value = 999;
	CList_Append(list, &third_value);

	CORE_Assert(
		(list->head != list->tail) &&
		(list->head->value == &first_value) &&
		(list->tail->value == &third_value)
	);

	CList_Free(&list);
}

void TEST_List_Prepend() {
	CList list;


	CList_Create(&list);

	// if first node - head and tail the same
	int first_value = 444;
	CList_Prepend(list, &first_value);

	CORE_Assert(list->head == list->tail);

	// if second node - head new, tail old 
	int second_value = 777;
	CList_Prepend(list, &second_value);

	CORE_Assert( 
			(list->head != list->tail) &&
			(list->head->value == &second_value) &&
			(list->tail->value == &first_value)
	);

	// if third node and so on - same behavior as with second node
	int third_value = 978;
	CList_Prepend(list, &third_value);

	CORE_Assert(
			(list->head != list->tail) &&
			(list->head->value == &third_value) &&
			(list->tail->value == &first_value)
	);

	CList_Free(&list);
}

void TEST_List_IsEmpty() 
{
	CList list;


	CList_Create(&list);

	// if head is NULL and tail is NULL - list is empty
	CORE_Assert(CList_IsEmpty(list) == true);
	
	// if head is NULL and tail is NOT NULL - list is NOT empty
	int pseudo_tail_node_value = -333;
	ListNode *pseudo_tail_node = CORE_MemAlloc(sizeof(ListNode), 1);
	pseudo_tail_node->value = &pseudo_tail_node_value;
	pseudo_tail_node->next = NULL;

	list->tail = pseudo_tail_node; 

	CORE_Assert(CList_IsEmpty(list) == false);
	
	CORE_MemFree(list->tail);
	list->tail = NULL;

	// if head is NOT NULL and tail is NULL - list is NOT empty
	int pseudo_head_node_value = -898;
	ListNode *pseudo_head_node = CORE_MemAlloc(sizeof(ListNode), 1);
	pseudo_head_node->value = &pseudo_head_node_value;
	pseudo_head_node->next = NULL;
	
	list->head = pseudo_head_node; 

	CORE_Assert(CList_IsEmpty(list) == false);

	CORE_MemFree(list->head);
	list->head = NULL;

	CList_Free(&list);
}

void TEST_List_Iterate() {
	int first  = 10;
	int second = 33;
	int third  = 99;
	int i 	   = 0;
	CList list;


	CList_Create(&list);
	CList_Append(list, &first);
	CList_Append(list, &second);
	CList_Append(list, &third);

	int *value_ptr;
	CList_ForEach(list, value_ptr)
	{
		if 		(i == 0) 	CORE_Assert(value_ptr == &first);
		else if (i == 1) 	CORE_Assert(value_ptr == &second);
		else if (i == 2) 	CORE_Assert(value_ptr == &third);

		i++;
	}
	CORE_Assert(value_ptr == NULL);

	CList_Free(&list);
}

int main() 
{
	TEST_List_Create();
	TEST_List_Append();
	TEST_List_Prepend();
	TEST_List_IsEmpty();
	TEST_List_Iterate();
	return 0;
}
