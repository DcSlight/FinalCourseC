#ifndef __EMPLOYEE__
#define __EMPLOYEE__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "General.h"

typedef enum {
	eDriver, eFactory, eGuide, eNofEmployeeTypes
} eEmployeeType;

static const char* EmployeeStr[eNofEmployeeTypes];

#define MIN_AGE 16

typedef struct _Employee Employee;

typedef void	(*fptrPrintEmployee)(Employee*);
typedef void	(*fptrFree)(Employee*);

typedef struct _Employee
{
	int id;
	void* pDerivedObj;
	char* name;
	int age;
	eEmployeeType type; //TODO: check to delete
	int seniority;
	//interface to access member functions
	fptrPrintEmployee print;
	fptrFree delete;
}Employee;

Employee* newEmployee(const char* pName, const int id, const int age, const eEmployeeType type, int seniority);	//constructor
void freeEmployee(Employee* const pEmployeeObj);	//destructor
void printEmployee(Employee* const pEmployeeObj);

#endif /* __EMPLOYEE__ */