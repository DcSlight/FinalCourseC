#include "DriverEmployee.h"

void initEmployeeDriver(Employee** pEmp)
{
	char* name;
	int age, seniority;
	char license;
	name = getStrExactName("Enter employee name:");
	printf("Enter employee age - minimum %d:\t", MIN_AGE);
	do {
		scanf("%d", &age);
		if (age < MIN_AGE)
		{
			printf("Not a valid age, Try again\n");
		}
	} while (age < MIN_AGE);
	printf("Enter employee seniority:\t");
	do {
		scanf("%d", &seniority);
		if (seniority > age - MIN_AGE)
		{
			printf("Not a valid seniority years, Try again\n");
		}
	} while (seniority > age - MIN_AGE);
	getchar();//clean buffer
	printf("Enter License:\t");
	scanf("%c", &license);
	printf("\n");
	*pEmp = newEmployeeDriver(name,age,eDriver,seniority,license);
}

Employee* newEmployeeDriver(const char* pName, const int age, const eEmployeeType type, int seniority, char license)
{
	EmployeeDriver* pEmpObj;
	Employee* pObj;
	pObj = newEmployee(pName,age,type,seniority);	//calling base class construtor
	//allocating memory
	pEmpObj = malloc(sizeof(EmployeeDriver));
	if (pEmpObj == NULL)
	{
		pObj->delete(pObj);
		return NULL;
	}
	pObj->pDerivedObj = pEmpObj; //pointing to derived object
	//initialising derived class members
	pEmpObj->license = license;
	//Changing base class interface to access derived class functions
	pObj->delete = deleteEmployeeDriver;
	pObj->print = printEmployeeDriver;
	return pObj;
}

void deleteEmployeeDriver(Employee* const pEmployeeObj)
{
	freeEmployee(pEmployeeObj); //license is char and doesn't need free
}

void printEmployeeDriver(Employee* const pEmployeeObj)
{
	printEmployee(pEmployeeObj);
	printf("Type: Driver\t");
	EmployeeDriver* pEmpDriverObj;
	pEmpDriverObj = pEmployeeObj->pDerivedObj;
	printf("License: %c\n", pEmpDriverObj->license);
}
