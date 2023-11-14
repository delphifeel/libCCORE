#include "../include/CCORE.h"

void test_core_string_records(void)
{
    const char *content = "\n\
        Id: 'Punch',\n\
        description: \n\
             'This is punch'\n\
    ";

    CORE_BuffInit(buff, content);

    CRecords records = CORE_StrSplitToRecords(buff, ":'", ',');

    char result[100];
    result[0] = 0;
    uint result_len = 0;
    CORE_StrCat(result, sizeof(result), result_len, "{");

    for (uint i = 0; i < records.size; i++) {
        CRecord *record = CRecords_Get(&records, i);
        char *k = CRecords_GetField(record, 0);
        char *v = CRecords_GetField(record, 2);
        CORE_StrPrintf(buff, sizeof(buff), "\"%s\": \"%s\";", k, v);
        CORE_StrCat(result, sizeof(result), result_len, buff);
    }
    CORE_StrCat(result, sizeof(result), result_len, "}");
    CORE_Assert(
        CORE_StrEqual(result, "{\"Id\": \"Punch\";\"description\": \"This is punch\";}")
    );

    CRecords_Free(&records);
}

void test_core_string_strcat(void)
{
    char buff[10];
    uint buff_len = 0;

    CORE_StrCat(buff, sizeof(buff), buff_len, "Hello");
    CORE_AssertIntEqual(buff_len, 5);
    CORE_Assert(CORE_StrEqual(buff, "Hello"));

    CORE_StrCat(buff, sizeof(buff), buff_len, "World");
    CORE_AssertIntEqual(buff_len, 9);
    CORE_Assert(CORE_StrEqual(buff, "HelloWorl"));
}

void test_core_string(void)
{
    test_core_string_records();
    test_core_string_strcat();
}
