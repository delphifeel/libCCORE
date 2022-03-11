#include "CCORE/CORE-disjoint-set.h"
#include "CCORE/CORE-memory.h"

CORE_OBJECT_INTERFACE(CDisjointSet,
	int 			*map_child_to_parent;
	uint 			map_child_to_parent_size;
	uint 			subsets_count;
);

/*****************************************************************************************************************************/

static void _FindSubset(CDisjointSet instance, int value, int *subset)
{
	int parent;


	if ((parent = instance->map_child_to_parent[value]) != -1) 
	{
		_FindSubset(instance, parent, subset);
	} 
	else 
	{
		*subset = value;
	}
}

/*****************************************************************************************************************************/

void CDisjointSet_Print(CDisjointSet instance)
{
	uint8 				processed_values[instance->map_child_to_parent_size];
	int 				current_parent;
	uint 				i;


	CORE_MemZero(processed_values, sizeof(processed_values));

	for (i = 0; i < instance->map_child_to_parent_size; i++)
	{
		if (processed_values[i] == 1) 
		{
			continue;
		}

		current_parent = i;
		processed_values[current_parent] = 1;

		while (instance->map_child_to_parent[current_parent] != -1)
		{
			current_parent = instance->map_child_to_parent[current_parent];
			processed_values[current_parent] = 1;
		}
	}
}

bool CDisjointSet_Union(CDisjointSet instance, int value1, int value2)
{
	int value1_subset;
	int value2_subset;


	_FindSubset(instance, value1, &value1_subset);
	_FindSubset(instance, value2, &value2_subset);

	if (value1_subset == value2_subset) 
	{
		return false;
	}

	instance->map_child_to_parent[value1_subset] = value2_subset;
	instance->subsets_count--;

	return true;
}

void CDisjointSet_GetSubsetsCount(CDisjointSet instance, uint *subsets_count)
{
	*subsets_count = instance->subsets_count;
}

/*****************************************************************************************************************************/

void CDisjointSet_Setup(CDisjointSet instance, uint size)
{
	instance->map_child_to_parent_size = size;
	instance->subsets_count = size;
	instance->map_child_to_parent = CORE_MemAlloc(sizeof(int), size);
	CORE_MemSet(instance->map_child_to_parent, -1, sizeof(int) * size);
}

/*****************************************************************************************************************************/

void CDisjointSet_Create(CDisjointSet *instance_ptr)
{
	CORE_OBJECT_CREATE(instance_ptr, CDisjointSet);

	(*instance_ptr)->map_child_to_parent_size = 0;
	(*instance_ptr)->map_child_to_parent = NULL;
	(*instance_ptr)->subsets_count = 0;
}

void CDisjointSet_Free(CDisjointSet *instance_ptr)
{
	CORE_MemFree((*instance_ptr)->map_child_to_parent);
	CORE_OBJECT_FREE(instance_ptr);
}

/*****************************************************************************************************************************/
