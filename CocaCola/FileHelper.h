#ifndef __FILE_HELPER__
#define __FILE_HELPER__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "General.h"

int		writeStringToFile(const char* str, FILE* fp, const char* msg);
int		writeCharsToFile(const char* arr, int size, FILE* fp, const char* msg);
int		writeIntToFile(int val, FILE* fp, const char* msg);

char*	readStringFromFile(FILE* fp, const char* msg);
int		readCharsFromFile(char* arr, int size, FILE* fp, const char* msg);
int		readIntFromFile(int* val, FILE* fp, const char* msg);

#endif


