#include "DriverEmployee.h"

static const char* licenseStr[eNofLicenseTypes]
= { "B", "C1", "C", "E" };

void initEmployeeDriver(Employee** pEmp)
{
	char* name;
	int age, seniority,id;
	eLicenseType license;
	printf("Enter employee id:\t");
	scanf("%d", &id);
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
			printf("Not a valid seniority years, Try again - maximum %d\n" , age - MIN_AGE);
		}
	} while (seniority > age - MIN_AGE);
	while ((getchar()) != '\n');// Clean the buffer
	license = getLicenseType();
	printf("\n");
	*pEmp = newEmployeeDriver(name,id,age,eDriver,seniority,license);
}

eLicenseType getLicenseType()
{
	int option;
	do {
		printf("Please enter one of the following types\n");
		for (int i = 0; i < eNofLicenseTypes; i++)
			printf("%d for %s\n", i, licenseStr[i]);
		scanf("%d", &option);
	} while (option < 0 || option >= eNofLicenseTypes);
	getchar();
	return (eLicenseType)option;
}

Employee* newEmployeeDriver(const char* pName,const int id, const int age, const eEmployeeType type, int seniority, eLicenseType license)
{
	EmployeeDriver* pEmpObj;
	Employee* pObj;
	pObj = newEmployee(pName,id,age,type,seniority);	//calling base class construtor
	//allocating memory
	pEmpObj = malloc(sizeof(EmployeeDriver));
	if (pEmpObj == NULL)
	{
		pObj->delete(pObj);
		return NULL;
	}
	pObj->pDerivedObj = pEmpObj; //pointing to derived object
	//initialising derived class members
	pEmpObj->licenseType = license;
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
	printf("\nLicense: %s\n", licenseStr[pEmpDriverObj->licenseType]);
}
