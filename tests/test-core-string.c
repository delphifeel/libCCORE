void test_core_string(void)
{
    const char *str = "   #include\"smth\"";
    const char *substr = "#include\"";
    const char *expected_str = CORE_StrFindEnd(str, CORE_StrLen(str), substr, CORE_StrLen(substr));
    CORE_Assert(CORE_StrEqual(expected_str, "smth\"") == true);

    str = " #in  #include\"smth\"";
    substr = "#include\"";
    expected_str = CORE_StrFindEnd(str, CORE_StrLen(str), substr, CORE_StrLen(substr));
    CORE_Assert(CORE_StrEqual(expected_str, "smth\"") == true);
}
