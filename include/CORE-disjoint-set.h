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

#include "CCORE/CORE-types.h"

typedef struct CDisjointSet_s CDisjointSet;

void 		 CDisjointSet_Print(const CDisjointSet *dset);
bool 	     CDisjointSet_Union(CDisjointSet *dset, int value1, int value2);
void 		 CDisjointSet_GetSubsetsCount(const CDisjointSet *dset, uint *subsets_count);

CDisjointSet *CDisjointSet_Create(uint size);
void 		 CDisjointSet_Free(CDisjointSet **dset);

#endif
