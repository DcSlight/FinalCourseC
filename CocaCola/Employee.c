#include "Employee.h"

static const char* EmployeeStr[eNofEmployeeTypes]
= { "Driver", "Guide" };

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

void freeEmployee(Employee* pEmp)
{
	free(pEmp->name);
}




