#ifndef _CORE_OBJECT_PRIVATE_H_
#define _CORE_OBJECT_PRIVATE_H_

#include "CORE-memory.h"
#include "CORE-debug.h"

#define _CObjectName(TYPE)                  (TYPE##_OBJECT_NAME)
#define _CObjectName_GetFunc(TYPE)          (TYPE##_OBJECT_NAME_GET)

#define _CORE_OBJECT_FIELDS(_INTERFACE)                                     \
    const char *_object_name;                                               \
    _INTERFACE                                                              

#define _CORE_OBJECT_DEFINE(TYPE)                                            \
    typedef struct TYPE##_STRUCT *(TYPE);                                   \
    extern const char *_CObjectName_GetFunc(TYPE)(void);                    \
    extern const char *TYPE##_GetObjectName(TYPE _instance)                 

#define _CORE_OBJECT_INTERFACE(TYPE, TYPE_STRUCT_INTERFACE)                          \
    struct TYPE##_STRUCT                                                            \
    {                                                                               \
        _CORE_OBJECT_FIELDS(TYPE_STRUCT_INTERFACE)                                  \
    };                                                                              \
                                                                                    \
    static const char *const _CObjectName(TYPE) = #TYPE;                            \
                                                                                    \
    const char *_CObjectName_GetFunc(TYPE)(void)                                    \
    {                                                                               \
        return _CObjectName(TYPE);                                                  \
    }                                                                               \
                                                                                    \
    const char *TYPE##_GetObjectName(TYPE _instance)                                \
    {                                                                               \
        return _instance->_object_name;                                             \
    }                                                                               \
                                                                                    \
    typedef TYPE _DUMMY_##TYPE                                                      

#define _CORE_OBJECT_CREATE(OBJECT_PTR, TYPE)   do {                            \
    CORE_AssertPointer(OBJECT_PTR);                                             \
    *(OBJECT_PTR) = CORE_MemAlloc(sizeof(struct TYPE##_STRUCT), 1);             \
    (*(OBJECT_PTR))->_object_name = _CObjectName(TYPE);                         \
} while (0)                                                                     


#define _CORE_OBJECT_FREE(OBJECT_PTR)    do {        \
    CORE_AssertPointer(OBJECT_PTR);                 \
    CORE_MemFree(*(OBJECT_PTR));                    \
    *(OBJECT_PTR) = NULL;                           \
} while (0)                                         

#define _CORE_AssertObjectType(OBJECT, TYPE)    do {                                                 \
    CORE_AssertPointer(OBJECT);                                                                     \
    CORE_AssertWithMessage(                                                                         \
        TYPE##_GetObjectName(OBJECT) == _CObjectName_GetFunc(TYPE)(),                               \
        "`%s` is not a `%s`\n", #OBJECT, #TYPE                                                      \
    );                                                                                              \
} while (0)                                                                                         


#endif