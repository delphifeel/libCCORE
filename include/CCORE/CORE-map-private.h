#ifndef _CORE_MAP_PRIVATE_H_
#define _CORE_MAP_PRIVATE_H_

#include "CORE-types.h"
#include "CORE-list.h"


typedef struct CMap_s 
{
    CList     **buckets;
    uint64      buckets_count;
    CList      *all_bucket_nodes;
} CMap;

typedef struct BucketNode_s 
{
    uint8      *key;
    uint        key_size;
    void       *value;
} BucketNode;

struct CMapIter_s
{
    ListNode *bucket_node_ptr;
};

extern void *_CMapIter_Next(struct CMapIter_s *iter);

#define _CMap_ForEach(MAP, ITEM)                                              \
    struct CMapIter_s ITEM##_iter = {map->all_bucket_nodes->head};             \
    while (ITEM = _CMapIter_Next(&ITEM##_iter))      


#endif