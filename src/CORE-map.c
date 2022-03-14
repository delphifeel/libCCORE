#include "CCORE/CORE-string.h"
#include "CCORE/CORE-map.h"
#include "CCORE/super_fast_hash.h"

static BucketNode *_CreateBucketNode(const char *key, uint64 key_size, void *value) 
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

static CList _FindBucket(CMap map, const char *key, uint64 key_size) 
{
	uint64 hash = SuperFastHash(key, key_size);
	uint64 bucket_index = hash % map->buckets_count; 
	return map->buckets[bucket_index];
}

static BucketNode *_FindBucketNode(CMap map, const char *key, uint64 key_size) 
{		
	BucketNode 	*result = NULL;
	CList 		bucket 	= _FindBucket(map, key, key_size);


	BucketNode *node;
	CList_ForEach(bucket, node)
	{
		if (node->key_size != key_size) 
			continue;

		if (CORE_MemEqual(node->key, key, key_size)) 
		{
			result = node;
			break;
		}	
	}

	return result;
}

void CMap_Create(CMap *map_ptr, uint64 map_size) 
{
	*map_ptr = CORE_MemAlloc(sizeof(struct CMap), 1);
	CMap map = *map_ptr;
	map->buckets = CORE_MemAlloc(sizeof(CList), map_size);
	for (uint64 i = 0; i < map_size; i++) 
	{
		CList_Create(&map->buckets[i]);
	}
	map->buckets_count = map_size;
}

void CMap_Free(CMap *map_ptr) 
{
	CMap 		map 	= *map_ptr;
	CList   	bucket 	= NULL;
	BucketNode 	*node;

	for (uint64 i = 0; i < map->buckets_count; i++) 
	{
		bucket = map->buckets[i];

		CList_ForEach(bucket, node)
		{
			_FreeBucketNode(node);
		}
		CList_Free(&map->buckets[i]);
	}

	CORE_MemFree(map->buckets);
	CORE_MemFree(*map_ptr);
}

void CMap_Set(CMap map, const char *key, void *value) 
{
	uint64 key_size = CORE_StrLen(key);
	BucketNode *bucket_node = _FindBucketNode(map, key, key_size);
	if (bucket_node)
	{
		bucket_node->value = value;
		return;
	}

	CList bucket = _FindBucket(map, key, key_size);
	BucketNode *new_node = _CreateBucketNode(key, key_size, value);	

	CList_Prepend(bucket, new_node);
}

void *CMap_Get(CMap map, const char *key) 
{
	BucketNode *bucketNode = _FindBucketNode(map, key, CORE_StrLen(key));
	return bucketNode == NULL ? NULL : bucketNode->value;
}
