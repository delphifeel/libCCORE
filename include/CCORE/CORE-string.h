#ifndef _CORE_STRING_H_
#define _CORE_STRING_H_

#include "CORE-types.h"

#define CORE_StrPrintf(DEST, DEST_SIZE, ...)	(snprintf(DEST, DEST_SIZE, __VA_ARGS__))
#define CORE_StrCat(DEST, DEST_SIZE, SRC)       (strncat(DEST, SRC, (DEST_SIZE - 1)))
#define CORE_StrCpy(DEST, DEST_SIZE, SRC)       (CORE_StrPrintf(DEST, DEST_SIZE, "%s", SRC))
#define CORE_StrEqual(STR1, STR2)               (strcmp(STR1, STR2) == 0)
#define CORE_StrLen(STR1)                       (strlen(STR1))
#define CORE_StrNewCopy(DEST, STR, STR_SIZE) \
    CORE_MemNewCopy(DEST, STR, STR_SIZE);    \
    DEST[STR_SIZE] = 0;
	
const char *CORE_StrFindEnd(const char *str, uint str_len, const char *substr, uint substr_len);

#ifdef CCORE_IMPL
const char *CORE_StrFindEnd(const char *str, uint str_len, const char *substr, uint substr_len)
{
    const char *str_pos = str;
    while (*str_pos != 0) {
        if (0 == strncmp(str_pos, substr, substr_len)) {
            return str_pos + substr_len;
        }
        str_pos++;
    }
    return NULL;
}
#endif

#endif
