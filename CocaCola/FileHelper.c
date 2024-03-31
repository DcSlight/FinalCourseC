#include "FileHelper.h"

int writeStringToFile(const char* str, FILE* fp, const char* msg)
{
	int length = (int)strlen(str);
	length++;
	if (!writeIntToFile(length, fp, msg))
		return 0;

	if (!writeCharsToFile(str, length, fp, msg))
		return 0;

	return 1;
}

int	 writeIntToFile(int val, FILE* fp, const char* msg)
{
	if (fwrite(&val, sizeof(int), 1, fp) != 1)
	{
		puts(msg);
		return 0;
	}
	return 1;
}

int	 writeCharsToFile(const char* arr, int size, FILE* fp, const char* msg)
{
	if (fwrite(arr, sizeof(char), size, fp) != size)
	{
		puts(msg);
		return 0;
	}
	return 1;
}
