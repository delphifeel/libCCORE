#ifndef _CORE_FILE_H_
#define _CORE_FILE_H_

#define CORE_FileWrite(FILE_NAME, BUFF, BUFF_SIZE) do {  \
    FILE *f = fopen(FILE_NAME,"wb");                    \
    if (!f) {                                                \
        CORE_DebugStdErr("Error open file %s\n", FILE_NAME); \
        break;                                               \
    }                                                        \
    fwrite(BUFF, BUFF_SIZE, 1, f);                          \
    fclose(f);                                             \
} while (0)

#endif
