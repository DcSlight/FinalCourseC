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
	return pObj;
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




