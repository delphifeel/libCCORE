#ifndef _CORE_MAP_H_
#define _CORE_MAP_H_

#include "CORE-map-private.h"

#define CMap_ForEach        _CMap_ForEach

void 	CMap_Create(CMap *instance_ptr, uint64 map_size);
void 	CMap_Free(CMap *instance_ptr);
void 	CMap_Set(CMap instance, const char *key, void *value);
void 	*CMap_Get(CMap instance, const char *key);

#endif

