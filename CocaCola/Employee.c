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
	pObj->writeTFile = writeEmployeeToTxtFile;
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
	printf("ID:%-10d\t", pEmp->id);
	printf("Name: %-15s \tAge: %-20d\t", pEmp->name, pEmp->age);
	printf("Seniority: %-10d\n", pEmp->seniority);
}

int writeEmployeeToBFile(FILE* fp, Employee* const pEmployeeObj)
{
	if (!writeIntToFile(pEmployeeObj->type, fp, "Error Writing Employee Type\n"))
		return 0;
	if (!writeIntToFile(pEmployeeObj->id, fp, "Error Writing Employee Id\n"))
		return 0;
	if (!writeStringToFile(pEmployeeObj->name, fp, "Error Writing Employee Name\n"))
		return 0;
	if (!writeIntToFile(pEmployeeObj->age, fp, "Error Writing Employee Age\n"))
		return 0;
	if (!writeIntToFile(pEmployeeObj->seniority, fp, "Error Writing Employee Seniority\n"))
		return 0;
	return 1;
}

int readEmployeeFromBFile(FILE* fp,int* id,int* age, int* seniority, char** name)
{
	if (!readIntFromFile(id, fp, "Error reading Employee id\n"))
		return 0;
	*name = readStringFromFile(fp, "Error reading Employee name\n");
	if (!*name)
		return 0;
	if (!readIntFromFile(age, fp, "Error reading Employee Age\n"))
		return 0;
	if (!readIntFromFile(seniority, fp, "Error reading Employee Seniority\n"))
		return 0;
	return 1;
}

int writeEmployeeToTxtFile(FILE* fp, Employee* const pEmployeeObj)
{
	if (!pEmployeeObj)
		return 0;
	fprintf(fp, "%d\n", pEmployeeObj->type);
	fprintf(fp, "%d\n", pEmployeeObj->id);
	fprintf(fp, "%s\n", pEmployeeObj->name);
	fprintf(fp, "%d\n", pEmployeeObj->age);
	fprintf(fp, "%d\n", pEmployeeObj->seniority);
	return 1;
}

int readEmployeeFromTxtFile(FILE* fp, Employee** pEmployeeObj, eEmployeeType type)
{
	char tempString[MAX_STR_LEN];
	if (!pEmployeeObj)
		return 0;

	int id, age,seniority;
	char* name;
	if (fscanf(fp, "%d", &id) != 1)
		return 0;

	myGets(tempString, MAX_STR_LEN, fp);
	name = getDynStr(tempString);

	if (fscanf(fp, "%d", &age) != 1)
		return 0;

	if (fscanf(fp, "%d", &seniority) != 1)
		return 0;

	*pEmployeeObj = newEmployee(name, id, age, type, seniority); //TODO: change
	return 1;
}

void freeEmployee(Employee* pEmp)
{
	free(pEmp->name);
	free(pEmp);
}




