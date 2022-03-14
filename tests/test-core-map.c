#include "CCORE.h"

void TEST_Map_Create(void)
{
    CMap map;


    CMap_Create(&map, 100);
    CMap_Free(&map);
}

void TEST_Map_SetData(void)
{
    CMap map; 
    double value1 = 3.33;
    double value2 = 4.991;


    CMap_Create(&map, 100);

    CMap_Set(map, "rabbit", &value1);
    CMap_Set(map, "wolf",  &value2);

    CORE_Assert(CMap_Get(map, "rabbit") == &value1);
    CORE_Assert(CMap_Get(map, "wolf") == &value2);
    CORE_Assert(CMap_Get(map, "something that dont exists") == NULL);

    int new_value = 333;
    CMap_Set(map, "wolf", &new_value);
    CORE_Assert(CMap_Get(map, "wolf") == &new_value);

    CMap_Free(&map);
}

void TEST_Map_SetObjectData(void)
{
    CMap map; 
    struct Coord 
    {
        uint x;
        uint y;
    };
    struct Coord *far_left = CORE_MemAlloc(sizeof(struct Coord), 1);
    far_left->x = 2;
    far_left->y = 4;


    CMap_Create(&map, 100);

    CMap_Set(map, "far left", far_left);

    struct Coord *temp = CMap_Get(map, "far left");
    CORE_Assert(
        (temp->x == far_left->x) &&
        (temp->y == far_left->y)
    );


    CORE_MemFree(far_left);
    CMap_Free(&map);
}

int main()
{
    TEST_Map_Create();
    TEST_Map_SetData();
    TEST_Map_SetObjectData();
    return 0;
}