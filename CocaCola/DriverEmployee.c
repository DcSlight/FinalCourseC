#include "DriverEmployee.h"

static const char* licenseStr[eNofLicenseTypes]
= { "B", "C1", "C", "E" };

void initEmployeeDriver(Employee** pEmp)
{
	char* name;
	int age, seniority,id;
	eLicenseType license;
	printf("Driver:\n");
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
	pObj->writeBFile = writeDriverToBFile;
	pObj->writeTFile = writeDriverToTxtFile;
	return pObj;
}

void deleteEmployeeDriver(Employee* const pEmployeeObj)
{



	//freeEmployee(pEmployeeObj); //license is char and doesn't need free
	EmployeeDriver* pEmpDriver;
	pEmpDriver = pEmployeeObj->pDerivedObj;
	//destroy derived obj
	free(pEmpDriver);
	//destroy base Obj
	freeEmployee(pEmployeeObj);

}

void printEmployeeDriver(Employee* const pEmployeeObj)
{
	printEmployee(pEmployeeObj);
	printf("\t\tType: Driver\t");
	EmployeeDriver* pEmpDriverObj;
	pEmpDriverObj = pEmployeeObj->pDerivedObj;
	printf("\tLicense: %-10s\n", licenseStr[pEmpDriverObj->licenseType]);
}

int writeDriverToBFile(FILE* fp, Employee* const pEmployeeObj)
{
	if (!writeEmployeeToBFile(fp, pEmployeeObj))
		return 0;
	EmployeeDriver* pEmpDriverObj;
	pEmpDriverObj = pEmployeeObj->pDerivedObj;
	if (!writeIntToFile(pEmpDriverObj->licenseType, fp, "Error Writing Driver License Type\n"))
		return 0;
	return 1;
}

int readDriverFromBFile(FILE* fp, Employee** pEmployeeObj)
{
	if (!pEmployeeObj)
		return 0;
	int license;
	int id, age, seniority;
	char* name;
	if (!readEmployeeFromBFile(fp,&id,&age,&seniority,&name))
		return 0;

	if (!readIntFromFile(&license, fp, "Error reading Driver License Type\n"))
		return 0;
	*pEmployeeObj = newEmployeeDriver(name,id,age,eDriver,seniority, license);
	free(name);
	return 1;
}

int writeDriverToTxtFile(FILE* fp, Employee* const pEmployeeObj)
{
	if (!writeEmployeeToTxtFile(fp, pEmployeeObj))
		return 0;
	EmployeeDriver* pEmpDriverObj;
	pEmpDriverObj = pEmployeeObj->pDerivedObj;
	fprintf(fp,"%d\n", pEmpDriverObj->licenseType);
	return 1;
}

int readDriverFromTxtFile(FILE* fp, Employee** pEmployeeObj)
{
	if (!pEmployeeObj)
		return 0;
	int license;
	if (!readEmployeeFromTxtFile(fp, pEmployeeObj, eDriver))
		return 0;
	if (fscanf(fp, "%d", &license) != 1)
		return 0;
	Employee* e = newEmployeeDriver((*pEmployeeObj)->name, (*pEmployeeObj)->id, (*pEmployeeObj)->age, (*pEmployeeObj)->type,
		(*pEmployeeObj)->seniority, license);
	(*pEmployeeObj)->delete((*pEmployeeObj));//free the old 
	*pEmployeeObj = e;//the new employeeGuide

	return 1;
}
