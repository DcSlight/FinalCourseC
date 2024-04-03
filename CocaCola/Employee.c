#include "Employee.h"



Employee* newEmployee(const char* pName,const int id, const int age, const eEmployeeType type, int seniority)
{
	Employee* pObj = NULL;
	//allocating memory
	pObj = (Employee*)malloc(sizeof(Employee));
	if (pObj == NULL)
	{
		return NULL;
	}
	pObj->pDerivedObj = NULL;// pObj; //pointing to itself
	pObj->name = malloc(sizeof(char) * (strlen(pName) + 1));
	if (pObj->name)
		strcpy(pObj->name, pName);
	pObj->id = id;
	pObj->age = age;
	pObj->type = type;
	pObj->seniority = seniority;

	//Initializing interface for access to functions
	pObj->print = printEmployee;
	pObj->delete = freeEmployee;//destructor pointing to destructor of itself
	pObj->writeBFile = writeEmployeeToBFile;
	pObj->readBFile = readEmployeeFromBFile;
	pObj->writeTFile = writeEmployeeToTxtFile;
	pObj->readTFile = readEmployeeFromTxtFile;
	return pObj;
}

eEmployeeType getEmployeeType()
{
	int option;
	do {
		printf("Please enter one of the following types\n");
		for (int i = 0; i < eNofEmployeeTypes; i++)
			printf("%d for %s\n", i, EmployeeStr[i]);
		scanf("%d", &option);
	} while (option < 0 || option >= eNofEmployeeTypes);
	getchar();
	return (eEmployeeType)option;
}

void printEmployee(Employee* const pEmp)
{
	printf("ID:%d\n", pEmp->id);
	printf("Name: %s \nAge: %d\n", pEmp->name, pEmp->age);
	printf("Seniority: %d\n", pEmp->seniority);
}

int writeEmployeeToBFile(FILE* fp, Employee* const pEmployeeObj)
{
	if (!writeIntToFile(pEmployeeObj->id, fp, "Error Writing Employee Id\n"))
		return 0;
	if (!writeStringToFile(pEmployeeObj->name, fp, "Error Writing Employee Name\n"))
		return 0;
	if (!writeIntToFile(pEmployeeObj->age, fp, "Error Writing Employee Age\n"))
		return 0;
	if (!writeIntToFile(pEmployeeObj->type, fp, "Error Writing Employee Type\n"))
		return 0;
	if (!writeIntToFile(pEmployeeObj->seniority, fp, "Error Writing Employee Seniority\n"))
		return 0;
	return 1;
}

int readEmployeeFromBFile(FILE* fp, Employee* pEmployeeObj)
{
	if (!readIntFromFile(&pEmployeeObj->id, fp, "Error reading Employee id\n"))
		return 0;
	pEmployeeObj->name = readStringFromFile(fp, "Error reading Employee name\n");
	if (!pEmployeeObj->name)
		return 0;
	if (!readIntFromFile(&pEmployeeObj->age, fp, "Error reading Employee Age\n"))
		return 0;
	int temp;
	if (!readIntFromFile(&temp, fp, "Error reading Employee Type\n"))
		return 0;
	pEmployeeObj->type = temp;
	if (!readIntFromFile(&pEmployeeObj->seniority, fp, "Error reading Employee Seniority\n"))
		return 0;
	pEmployeeObj->pDerivedObj = NULL;
	pEmployeeObj->print = printEmployee;
	pEmployeeObj->delete = freeEmployee;
	pEmployeeObj->writeBFile = writeEmployeeToBFile;
	pEmployeeObj->readBFile = readEmployeeFromBFile;
	pEmployeeObj->writeTFile = writeEmployeeToTxtFile;
	pEmployeeObj->readTFile = readEmployeeFromTxtFile;
	return 1;
}

int writeEmployeeToTxtFile(FILE* fp, Employee* const pEmployeeObj)
{
	if (!pEmployeeObj)
		return 0;
	fprintf(fp, "%d\n", pEmployeeObj->id);
	fprintf(fp, "%s\n", pEmployeeObj->name);
	fprintf(fp, "%d\n", pEmployeeObj->age);
	fprintf(fp, "%d\n", pEmployeeObj->type);
	fprintf(fp, "%d\n", pEmployeeObj->seniority);
	return 1;
}

int readEmployeeFromTxtFile(FILE* fp, Employee* pEmployeeObj)
{
	char tempString[MAX_STR_LEN];
	if (!pEmployeeObj)
		return 0;

	int tempInt;
	if (fscanf(fp, "%d", &tempInt) != 1)
		return 0;
	pEmployeeObj->id = tempInt;

	myGets(tempString, MAX_STR_LEN, fp);
	pEmployeeObj->name = getDynStr(tempString);

	if (fscanf(fp, "%d", &tempInt) != 1)
		return 0;
	pEmployeeObj->age = tempInt;

	if (fscanf(fp, "%d", &tempInt) != 1)
		return 0;
	pEmployeeObj->type = tempInt;

	if (fscanf(fp, "%d", &tempInt) != 1)
		return 0;
	pEmployeeObj->seniority = tempInt;
	pEmployeeObj->pDerivedObj = NULL;
	pEmployeeObj->print = printEmployee;
	pEmployeeObj->delete = freeEmployee;
	pEmployeeObj->writeBFile = writeEmployeeToBFile;
	pEmployeeObj->readBFile = readEmployeeFromBFile;
	pEmployeeObj->writeTFile = writeEmployeeToTxtFile;
	pEmployeeObj->readTFile = readEmployeeFromTxtFile;
	return 1;
}

void freeEmployee(Employee* pEmp)
{
	free(pEmp->name);
}




