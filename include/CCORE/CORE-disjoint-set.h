/**
 * @defgroup   CORE-disjoint-set
 *
 * @brief      
 	Disjoint set.
	Created from numbers according to setup size.

	Example: 
		for size 10 will be created 10 sets
		{0} {1} {2} {3} {4} {5} {6} {7} {8} {9}
 *
 * @author     Delphifeel
 * @date       2022
 */

#ifndef _CORE_DISJOINT_SET_H_
#define _CORE_DISJOINT_SET_H_

#include "CORE-types.h"
#include "CORE-object.h"

CORE_OBJECT_DEFINE(CDisjointSet);

void 		CDisjointSet_Print(CDisjointSet instance);
bool 	    CDisjointSet_Union(CDisjointSet instance, int value1, int value2);
void 		CDisjointSet_GetSubsetsCount(CDisjointSet instance, uint *subsets_count);

void 		CDisjointSet_Setup(CDisjointSet instance, uint size);

void 		CDisjointSet_Create(CDisjointSet *instance_ptr);
void 		CDisjointSet_Free(CDisjointSet *instance_ptr);

#endif
