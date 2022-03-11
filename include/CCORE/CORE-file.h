#ifndef _CORE_FILE_H_
#define _CORE_FILE_H_

#include <stdio.h>

#define CFile_Open              fopen
#define CFile_Close             fclose
#define CFile_Read              fread
#define CFile_Write             fwrite

typedef FILE* CFile;

#endif
