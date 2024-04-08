#ifndef __EMPLOYEE_GUIDE__
#define __EMPLOYEE_GUIDE__

#include <stdio.h>
#include <stdlib.h>
#include "HistoricalEvent.h"
#include "Employee.h"

typedef enum {
	eHighSchool, eAcademic, eCourse, eNofEducationLevel
} eEducationLevel;

static const char* EducationLevelStr[eNofEducationLevel];

typedef struct _EmployeeGuide EmployeeGuide;

typedef void (*fptrTellFact)(Employee*, HistoricalEvent*);

typedef struct _EmployeeGuide
{
	Employee* pBaseObj;
	eEducationLevel educationLevel;
	//interface to access member functions
	fptrTellFact tellFact;
}EmployeeGuide;

void initEmployeeGuide(Employee** pEmp, Employee** allEmployees, int employeesCount);
eEducationLevel getEducationLevel();
Employee* newEmployeeGuide(const char* pName, const int id, const int age, const eEmployeeType type, int seniority, eEducationLevel educationLevel);//constructor
void deleteEmployeeGuide(Employee* const pEmployeeObj);	//destructor
void printEmployeeGuide(Employee* const pEmployeeObj);
void tellFact(Employee* const pEmployeeObj, HistoricalEvent* pEvent);

int writeGuideToBFile(FILE* fp, Employee* const pEmployeeObj);
int readGuideFromBFile(FILE* fp, Employee** pEmployeeObj);
int writeGuideToTxtFile(FILE* fp, Employee* const pEmployeeObj);
int readGuideFromTxtFile(FILE* fp, Employee** pEmployeeObj);

#endif /* __EMPLOYEE_GUIDE__ */
