#ifndef __EMPLOYEE_GUIDE__
#define __EMPLOYEE_GUIDE__

#include <stdio.h>
#include <stdlib.h>

#include "Employee.h"

typedef enum {
	eHighSchool, eAcademic, eCourse, eNofEducationLevel
} eEducationLevel;

static const char* EducationLevelStr[eNofEducationLevel];

typedef struct _EmployeeGuide EmployeeGuide;

typedef void (*fptrTellFact)(Employee*);

typedef struct _EmployeeGuide
{
	Employee* pBaseObj;
	eEducationLevel educationLevel;
	//interface to access member functions
	fptrTellFact tellFact;
}EmployeeGuide;

void initEmployeeGuide(Employee** pEmp);
eEducationLevel getEducationLevel();
Employee* newEmployeeGuide(const char* pName, const int age, const eEmployeeType type, int seniority, eEducationLevel educationLevel);//constructor
void deleteEmployeeGuide(Employee* const pEmployeeObj);	//destructor
void printEmployeeGuide(Employee* const pEmployeeObj);
void tellFact(Employee* const pEmployeeObj);

#endif /* __EMPLOYEE_GUIDE__ */
