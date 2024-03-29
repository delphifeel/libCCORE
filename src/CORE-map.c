#include "CCORE/CORE-string.h"
#include "CCORE/CORE-map.h"
#include "CCORE/super_fast_hash.h"

static BucketNode *_CreateBucketNode(const uint8 *key, uint key_size, void *value) 
{
    BucketNode *bucketNode = CORE_MemAlloc(sizeof(BucketNode), 1);
    CORE_MemNewCopy(bucketNode->key, key, key_size);
    bucketNode->key_size = key_size;
    bucketNode->value = value;

    return bucketNode;
}

static void _FreeBucketNode(BucketNode *node)
{
    CORE_MemFree(node->key);
    CORE_MemFree(node);
}

static CList *_GetBucket(const CMap *map, const uint8 *key, uint key_size) 
{
    uint64 hash = SuperFastHash((const char *) key, key_size);
    uint64 bucket_index = hash % map->buckets_count; 
    return map->buckets[bucket_index];
}

static BucketNode *_FindBucketNode(const CMap *map, const uint8 *key, uint key_size) 
{       
    BucketNode  *result = NULL;
    CList       *bucket  = _GetBucket(map, key, key_size);


    BucketNode *node;
    CList_ForEach(bucket, node) {
        if (node->key_size != key_size) {
            continue;
        }

        if (CORE_MemEqual(node->key, key, key_size)) {
            result = node;
            break;
        }   
    }

    return result;
}

void *_CMapIter_Next(struct CMapIter_s *iter)
{
    if (iter->bucket_node_ptr == NULL) {
        return NULL;
    }

    BucketNode *bucket_node = iter->bucket_node_ptr->value;
    iter->bucket_node_ptr = iter->bucket_node_ptr->next;
    return bucket_node->value;
}

void CMap_Set(CMap *map, const uint8 *key, uint key_size, void *value) 
{
    BucketNode  *bucket_node  = _FindBucketNode(map, key, key_size);

    if (bucket_node) {
        bucket_node->value = value;
        return;
    }

    CList       *bucket      = _GetBucket(map, key, key_size);
    BucketNode  *new_node    = _CreateBucketNode(key, key_size, value); 

    CList_Prepend(bucket, new_node);
    CList_Prepend(map->all_bucket_nodes, new_node);
}

void *CMap_Get(const CMap *map, const uint8 *key, uint key_size) 
{
    BucketNode *bucketNode = _FindBucketNode(map, key, key_size);
    return bucketNode == NULL ? NULL : bucketNode->value;
}

CMap *CMap_Create(uint64 map_size) 
{
    CMap *map    = CORE_MemAlloc(sizeof(CMap), 1);
    map->buckets = CORE_MemAlloc(sizeof(CList), map_size);

    for (uint64 i = 0; i < map_size; i++) {
        map->buckets[i] = CList_Create();
    }
    map->buckets_count = map_size;
    map->all_bucket_nodes = CList_Create();
    return map;
}

void CMap_Free(CMap **map_ptr) 
{
    BucketNode  *node;
    CMap        *map = *map_ptr;

    CList_ForEach(map->all_bucket_nodes, node) {
        _FreeBucketNode(node);
    }
    CList_Free(&map->all_bucket_nodes);

    for (uint64 i = 0; i < map->buckets_count; i++) {
        CList_Free(&map->buckets[i]);
    }
    CORE_MemFree(map->buckets);
    CORE_MemFree(*map_ptr);
}
