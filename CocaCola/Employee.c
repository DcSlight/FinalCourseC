#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Employee.h"
#include "General.h"

void initEmployee(Employee* pEmp)
{
	pEmp->name = getStrExactName("Enter employee name:");
	printf("Enter employee age:\t");
	scanf("%d", &pEmp->age);
	printf("\n");
}

void printEmployee(const Employee* pEmp)
{
	printf("Name: %s \tAge: %d\n", pEmp->name, pEmp->age);
}

void freeEmployee(Employee* pEmp)
{
	free(pEmp->name);
}




