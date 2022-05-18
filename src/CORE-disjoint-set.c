#include "CCORE/CORE-disjoint-set.h"
#include "CCORE/CORE-memory.h"

struct CDisjointSet_s
{
	uint 			child_to_parent_size;
	uint 			subsets_count;
	int 			*child_to_parent;
};

/*****************************************************************************************************************************/

static void _FindSubset(const CDisjointSet *dset, int value, int *subset)
{
	int parent;


	if ((parent = dset->child_to_parent[value]) != -1) {
		_FindSubset(dset, parent, subset);
	} else {
		*subset = value;
	}
}

/*****************************************************************************************************************************/

void CDisjointSet_Print(const CDisjointSet *dset)
{
	uint8 				processed_values[dset->child_to_parent_size];
	int 				current_parent;
	uint 				i;


	CORE_MemZero(processed_values, sizeof(processed_values));

	for (i = 0; i < dset->child_to_parent_size; i++)
	{
		if (processed_values[i] == 1) 
		{
			continue;
		}

		current_parent = i;
		processed_values[current_parent] = 1;

		while (dset->child_to_parent[current_parent] != -1)
		{
			current_parent = dset->child_to_parent[current_parent];
			processed_values[current_parent] = 1;
		}
	}
}

bool CDisjointSet_Union(CDisjointSet *dset, int value1, int value2)
{
	int value1_subset;
	int value2_subset;


	_FindSubset(dset, value1, &value1_subset);
	_FindSubset(dset, value2, &value2_subset);

	if (value1_subset == value2_subset) 
	{
		return false;
	}

	dset->child_to_parent[value1_subset] = value2_subset;
	dset->subsets_count--;

	return true;
}

void CDisjointSet_GetSubsetsCount(const CDisjointSet *dset, uint *subsets_count)
{
	*subsets_count = dset->subsets_count;
}

/*****************************************************************************************************************************/

static void _Setup(CDisjointSet *dset, uint size)
{
	dset->child_to_parent_size = size;
	dset->subsets_count = size;
	dset->child_to_parent = CORE_MemAlloc(sizeof(int), size);
	CORE_MemSet(dset->child_to_parent, -1, sizeof(int) * size);
}

/*****************************************************************************************************************************/

CDisjointSet *CDisjointSet_Create(uint size)
{
	CDisjointSet *dset = CORE_MemAlloc(sizeof(CDisjointSet), 1);
	_Setup(dset, size);
	return dset;
}

void CDisjointSet_Free(CDisjointSet **dset)
{
	CDisjointSet *dset_value = *dset;
	CORE_MemFree(dset_value->child_to_parent);
	CORE_MemFree(dset_value);
}

/*****************************************************************************************************************************/
