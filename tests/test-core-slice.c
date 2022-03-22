#include "CCORE.h"

void TEST_Slice_Append(void) 
{
	CSlice slice;
	char *str1 = "Hello, ";
	char *str2 = "World.";


	CSlice_Create(&slice, 10);

	CSlice_Append(slice, str1);
	CSlice_Append(slice, str2);

	CORE_AssertWithMessage(
		(CSlice_Get(slice, 0) == str1) &&
		(CSlice_Get(slice, 1) == str2),
		"adding 2 strings works correctly."
	);

	CSlice_Free(&slice);
}

void TEST_Slice_BigAppend(void)
{
	CSlice slice;

	CSlice_Create(&slice, 10);

	char *loop_str = "THIS WILL BE LOOPED...";
	for (int i = 0; i < 100; i++) 
	{
		CSlice_Append(slice, loop_str);
	}

	int result = 1;

	for (int i = 0; i < 100; i++) 
	{
		result = result && CSlice_Get(slice, i) == loop_str;
	}

	CORE_AssertWithMessage(result, "adding string 100 times works correctly");

	CSlice_Free(&slice);
}

void TEST_Slice_ChangeValue(void)
{
	CSlice slice;
	int some_value = 666;
	int some_new_value = -999;

	CSlice_Create(&slice, 10);

	CSlice_Append(slice, &some_value);
	CSlice_Append(slice, &some_new_value);
	CORE_Assert(CSlice_Get(slice, 0) == &some_value);
	CORE_Assert(CSlice_Pop(slice) == &some_new_value);
	CORE_Assert(CSlice_Pop(slice) == &some_value);

	CSlice_Append(slice, &some_value);
	int *some_value_ptr = CSlice_Get(slice, 0);
	*some_value_ptr = 333;
	CORE_Assert(CSlice_Pop(slice) == &some_value);
	CORE_Assert(some_value == 333);

	CSlice_Free(&slice);
}

int main()
{
	TEST_Slice_Append();
	TEST_Slice_BigAppend();
	TEST_Slice_ChangeValue();
	return 0;
}

