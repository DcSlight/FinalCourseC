#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Supplier.h"
#include "General.h"

void initSupplier(Supplier* pSupplier)
{
	printf("Enter supplier id:\t");
	scanf("%d", &pSupplier->id);
	pSupplier->name = getStrExactName("Enter supplier name:");
	printf("Enter a phone number:\t");
	scanf("%s", pSupplier->phoneNo);
	initAddress(&pSupplier->address);
}

void printSupplier(const Supplier* pSupplier)
{
	printf("ID: %d\n", pSupplier->id);
	printf("Supplier: %s\n", pSupplier->name);
	printf("Phone No: %s\n", pSupplier->phoneNo);
	printAddress(&pSupplier->address);
}

void freeSupplier(Supplier* pSupplier)
{
	free(pSupplier->name);
}


