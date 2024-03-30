#ifndef __EMPLOYEE_DRIVER__
#define __EMPLOYEE_DRIVER__

#include <stdio.h>
#include <stdlib.h>
#include "Employee.h"

typedef struct _EmployeeDriver EmployeeDriver;

typedef struct _EmployeeDriver
{
	Employee* pBaseObj;
	char license;
}EmployeeDriver;

void initEmployeeDriver(Employee** pEmp);
Employee* newEmployeeDriver(const char* pName, const int age, const eEmployeeType type, int seniority,char license);//constructor
void deleteEmployeeDriver(Employee* const pEmployeeObj);	//destructor
void printEmployeeDriver(Employee* const pEmployeeObj);

#endif /* __EMPLOYEE_DRIVER__ */
