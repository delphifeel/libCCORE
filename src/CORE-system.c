#ifdef _WIN32
	#error "CORE-system not implemented"
#else
	#include <unistd.h>
#endif

#include "CCORE/CORE-system.h"
#include "CCORE/CORE-file.h"
#include "CCORE/CORE-debug.h"

/*****************************************************************************************************************************/

bool CORE_GenerateRandomDataToBuffer(uint8 buffer[], uint buffer_size)
{
	CFile 	file;
	uint  	read_size;


	file = CFile_Open("/dev/urandom", "re");
	if (file == NULL) 
	{
		return false;
	}

	read_size = CFile_Read(buffer, sizeof(uint8), buffer_size, file);
	if (read_size != buffer_size)
	{
		CFile_Close(file);
		return false;
	}

	CFile_Close(file);
	return true;
}

bool CORE_GenerateUIDToBuffer(uint8 buffer[UID_SIZE])
{
	return CORE_GenerateRandomDataToBuffer(buffer, UID_SIZE);
}

void CORE_Sleep(uint seconds)
{
	sleep(seconds);
}

/*****************************************************************************************************************************/
