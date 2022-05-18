#include "CCORE.h"

void TEST_Map_Create(void)
{
    CMap *map = CMap_Create(100);
    CMap_Free(&map);
}

void TEST_Map_SetData(void)
{
    CMap *map = CMap_Create(100);
    double value1 = 3.33;
    double value2 = 4.991;

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
    CMap *map = CMap_Create(100);
    struct Coord 
    {
        uint x;
        uint y;
    };
    struct Coord *far_left = CORE_MemAlloc(sizeof(struct Coord), 1);
    far_left->x = 2;
    far_left->y = 4;

    CMap_Set(map, "far left", far_left);
    struct Coord *temp = CMap_Get(map, "far left");
    CORE_Assert(
        (temp->x == far_left->x) &&
        (temp->y == far_left->y)
    );

    CORE_MemFree(far_left);
    CMap_Free(&map);
}

void TEST_Map_Iteration(void)
{
    CMap    *map = CMap_Create(10);

    int *value;
    CMap_ForEach(map, value) {
        CORE_Assert(1 == 2);
    }

    uint bob_height = 165;
    uint bob_age = 44;
    uint error_code = 1;

    CMap_Set(map, "bob_height", &bob_height);
    CMap_Set(map, "bob_age", &bob_age);
    CMap_Set(map, "error_code", &error_code);

    uint *value_ptr;
    CMap_ForEach(map, value_ptr) {
        CORE_Assert(
            (value_ptr == &bob_height) ||
            (value_ptr == &bob_age) ||
            (value_ptr == &error_code)
        );
    }

    CORE_Assert(CMap_Get(map, "bob_height") == &bob_height);
    CORE_Assert(CMap_Get(map, "bob_age") == &bob_age);
    CORE_Assert(CMap_Get(map, "error_code") == &error_code);

    CMap_Free(&map);
}

int main()
{
    TEST_Map_Create();
    TEST_Map_SetData();
    TEST_Map_SetObjectData();
    TEST_Map_Iteration();
    return 0;
}