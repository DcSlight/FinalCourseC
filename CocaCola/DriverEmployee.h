#ifndef __EMPLOYEE_DRIVER__
#define __EMPLOYEE_DRIVER__

#include <stdio.h>
#include <stdlib.h>
#include "Employee.h"

typedef enum {
	eB, eC1, eC, eE, eNofLicenseTypes
} eLicenseType;

static const char* licenseStr[eNofLicenseTypes];

typedef struct _EmployeeDriver EmployeeDriver;

typedef struct _EmployeeDriver
{
	Employee* pBaseObj;
	eLicenseType licenseType;
}EmployeeDriver;

void initEmployeeDriver(Employee** pEmp);
eLicenseType getLicenseType();
Employee* newEmployeeDriver(const char* pName,const int id, const int age, const eEmployeeType type, int seniority, eLicenseType license);//constructor
void deleteEmployeeDriver(Employee* const pEmployeeObj);	//destructor
void printEmployeeDriver(Employee* const pEmployeeObj);

int writeDriverToBFile(FILE* fp, Employee* const pEmployeeObj);
int readDriverFromBFile(FILE* fp, Employee** pEmployeeObj);
int writeDriverToTxtFile(FILE* fp, Employee* const pEmployeeObj);
int readDriverFromTxtFile(FILE* fp, Employee* pEmployeeObj);

#endif /* __EMPLOYEE_DRIVER__ */
