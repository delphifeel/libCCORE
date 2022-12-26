#ifndef _CORE_STRING_H_
#define _CORE_STRING_H_

#include "CORE-types.h"

#define CORE_StrPrintf(DEST, DEST_SIZE, ...)	(snprintf(DEST, DEST_SIZE, __VA_ARGS__))
#define CORE_StrCat(DEST, DEST_SIZE, SRC)       (strncat(DEST, SRC, (DEST_SIZE - 1)))
#define CORE_StrCpy(DEST, DEST_SIZE, SRC)       (CORE_StrPrintf(DEST, DEST_SIZE, "%s", SRC))
#define CORE_StrEqual(STR1, STR2)               (strcmp(STR1, STR2) == 0)
#define CORE_StrLen(STR1)                       (strlen(STR1))

#endif
