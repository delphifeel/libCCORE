#ifndef _CORE_MAP_H_
#define _CORE_MAP_H_

#include "CORE-map-private.h"

#define CMap_ForEach        _CMap_ForEach

CMap   *CMap_Create(uint64 map_size);
void    CMap_Free(CMap **map_ptr);
void    CMap_Set(CMap *map, const uint8 *key, uint key_size, void *value);
void   *CMap_Get(const CMap *map, const uint8 *key, uint32 key_size);

#endif

