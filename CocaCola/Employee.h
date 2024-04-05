#ifndef __EMPLOYEE__
#define __EMPLOYEE__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "General.h"
#include "FileHelper.h"

typedef enum {
	eDriver, eGuide, eNofEmployeeTypes
} eEmployeeType;

static const char* EmployeeStr[eNofEmployeeTypes] = { "Driver", "Guide" };
#define MIN_AGE 16

typedef struct _Employee Employee;

typedef void	(*fptrPrintEmployee)(Employee*);
typedef void	(*fptrFree)(Employee*);
typedef int	(*fptrWriteBFile)(FILE*,Employee* const);
typedef int	(*fptrWriteTFile)(FILE*,Employee* const);

typedef struct _Employee
{
	int id;
	void* pDerivedObj;
	char* name;
	int age;
	eEmployeeType type;
	int seniority;
	//interface to access member functions
	fptrPrintEmployee print;
	fptrFree delete;
	fptrWriteBFile writeBFile;
	fptrWriteTFile writeTFile;
}Employee;

Employee* newEmployee(const char* pName, const int id, const int age, const eEmployeeType type, int seniority);	//constructor
eEmployeeType getEmployeeType();
void freeEmployee(Employee* const pEmployeeObj);	//destructor
void printEmployee(Employee* const pEmployeeObj);
int writeEmployeeToBFile(FILE* fp, Employee* const pEmployeeObj);
int readEmployeeFromBFile(FILE* fp, Employee** pEmployeeObj, eEmployeeType type);
int writeEmployeeToTxtFile(FILE* fp, Employee* const pEmployeeObj);
int readEmployeeFromTxtFile(FILE* fp, Employee** pEmployeeObj, eEmployeeType type);

#endif /* __EMPLOYEE__ */