#ifndef _CORE_MAP_PRIVATE_H_
#define _CORE_MAP_PRIVATE_H_

#include "CORE-types.h"
#include "CORE-list.h"


typedef struct CMap {
    CList       *buckets;
    uint64      buckets_count;
} *CMap;

typedef struct BucketNode {
    char        *key;
    uint        key_size;
    void        *value;
} BucketNode;

#endif