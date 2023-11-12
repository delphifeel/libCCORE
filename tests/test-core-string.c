#include "../include/CCORE.h"

void test_core_string(void)
{

    const char *content = "\n\
        Id: 'Punch',\n\
        description: \n\
             'This is punch'\n\
    ";

    CORE_BuffInit(buff, content);

    CRecords records = CORE_StrSplitToRecords(buff, ":'", ',');

    char result[1200];
    result[0] = 0;
    CORE_StrCat(result, sizeof(result), "{");

    for (uint i = 0; i < records.size; i++) {
        CRecord *record = CRecords_Get(&records, i);
        char *k = CRecords_GetField(record, 0);
        char *v = CRecords_GetField(record, 2);
        CORE_StrPrintf(buff, sizeof(buff), "\"%s\": \"%s\";", k, v);
        CORE_StrCat(result, sizeof(result), buff);
    }
    CORE_StrCat(result, sizeof(result), "}");
    CORE_Assert(
        CORE_StrEqual(result, "{\"Id\": \"Punch\";\"description\": \"This is punch\";}")
    );

    CRecords_Free(&records);
}
