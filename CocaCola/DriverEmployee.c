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
	pObj->readBFile = readDriverFromBFile;
	pObj->writeTFile = writeDriverToTxtFile;
	pObj->readTFile = readDriverFromTxtFile;
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

int readDriverFromBFile(FILE* fp, Employee* pEmployeeObj)
{
	if (!readEmployeeFromBFile(fp, pEmployeeObj))
		return 0;
	EmployeeDriver* pEmpDriverObj;
	pEmpDriverObj = malloc(sizeof(EmployeeDriver));
	if (pEmpDriverObj == NULL)
	{
		pEmployeeObj->delete(pEmployeeObj);
		return 0;
	}
	int tmp;
	if (!readIntFromFile(&tmp, fp, "Error reading Driver License Type\n"))
		return 0;

	pEmployeeObj->pDerivedObj = pEmpDriverObj;
	pEmpDriverObj->licenseType = tmp;
	//Changing base class interface to access derived class functions
	pEmployeeObj->delete = deleteEmployeeDriver;
	pEmployeeObj->print = printEmployeeDriver;
	pEmployeeObj->writeBFile = writeDriverToBFile;
	pEmployeeObj->readBFile = readDriverFromBFile;
	pEmployeeObj->writeTFile = writeDriverToTxtFile;
	pEmployeeObj->readTFile = readDriverFromTxtFile;
	return 1;
}

int writeDriverToTxtFile(FILE* fp, Employee* const pEmployeeObj)
{
	if (!writeEmployeeToTxtFile(fp, pEmployeeObj))
		return 0;
	EmployeeDriver* pEmpDriverObj;
	pEmpDriverObj = pEmployeeObj->pDerivedObj;
	fprintf(fp,"%d", pEmpDriverObj->licenseType);
	return 1;
}

int readDriverFromTxtFile(FILE* fp, Employee* pEmployeeObj)
{
	if (!readEmployeeFromTxtFile(fp, pEmployeeObj))
		return 0;
	EmployeeDriver* pEmpDriverObj;
	pEmpDriverObj = malloc(sizeof(EmployeeDriver));
	if (pEmpDriverObj == NULL)
	{
		pEmployeeObj->delete(pEmployeeObj);
		return 0;
	}
	int tempInt;
	if (fscanf(fp, "%d", &tempInt) != 1)
		return 0;
	pEmployeeObj->pDerivedObj = pEmpDriverObj;
	pEmpDriverObj->licenseType = tempInt;
	//Changing base class interface to access derived class functions
	pEmployeeObj->delete = deleteEmployeeDriver;
	pEmployeeObj->print = printEmployeeDriver;
	pEmployeeObj->writeBFile = writeDriverToBFile;
	pEmployeeObj->readBFile = readDriverFromBFile;
	pEmployeeObj->writeTFile = writeDriverToTxtFile;
	pEmployeeObj->readTFile = readDriverFromTxtFile;
	return 1;
}
