#include "CCORE.h"

void TEST_List_Create() 
{
	CList *list = CList_Create();

	CORE_Assert(list != NULL);	
	CORE_Assert(list->head == NULL);
	CORE_Assert(list->tail == NULL);

	CList_Free(&list);
}

void TEST_List_Append() {
	CList *list = CList_Create();

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
	CList *list = CList_Create();

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
	CList *list = CList_Create();

	// if head is NULL and tail is NULL - list is empty
	CORE_Assert(CList_IsEmpty(list));
	
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
	CList *list = CList_Create();

	CList_Append(list, &first);
	CList_Append(list, &second);
	CList_Append(list, &third);

	int *value_ptr;
	CList_ForEach(list, value_ptr) {
		if 		(i == 0) 	CORE_Assert(value_ptr == &first);
		else if (i == 1) 	CORE_Assert(value_ptr == &second);
		else if (i == 2) 	CORE_Assert(value_ptr == &third);

		i++;
	}
	CORE_Assert(value_ptr == NULL);

	CList_Free(&list);
}

void TEST_List_Remove() {
	int numbers[6] = {1, 2, 3, 4, 5, 6};
	CList *list = CList_Create();

	for (int i = 0; i < 6; i++) {
		CList_Append(list, numbers + i);
	}

	int *value_ptr;
	int i = 0;
	CList_ForEach(list, value_ptr) {
		CORE_Assert(value_ptr == numbers + i);
		i++;
	}

	// Remove 1
	CList_Remove(list, &numbers[0]);
	// Remove 3
	CList_Remove(list, &numbers[2]);
	// Remove 5
	CList_Remove(list, &numbers[4]);
	// Remove 6
	CList_Remove(list, &numbers[5]);

	i = 0;
	int *value_ptr_2;
	CList_ForEach(list, value_ptr_2)
	{
		if (i == 0) { CORE_Assert(value_ptr_2 == &numbers[1]);	}
		else if (i == 1) { CORE_Assert(value_ptr_2 == &numbers[3]);	}
		i++;
	}
	CORE_Assert(list->head->value == &numbers[1]);
	CORE_Assert(list->tail->value == &numbers[3]);

	CORE_Assert(CList_Remove(list, &numbers[0]) == false);
	CList_Remove(list, &numbers[1]);
	CORE_Assert(list->head->value == &numbers[3]);
	CORE_Assert(list->tail->value == &numbers[3]);


	CList_Free(&list);
}

int main() 
{
	TEST_List_Create();
	TEST_List_Append();
	TEST_List_Prepend();
	TEST_List_IsEmpty();
	TEST_List_Iterate();
	TEST_List_Remove();
	return 0;
}
