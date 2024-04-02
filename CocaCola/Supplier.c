#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Supplier.h"
#include "General.h"

void initSupplier(Supplier* pSupplier, Supplier** allSuppliers,int suppliersCount)
{
	getSupplierId(pSupplier, allSuppliers, suppliersCount);
	pSupplier->name = getStrExactName("Enter supplier name:");
	printf("Enter a phone number:\t");
	scanf("%s", pSupplier->phoneNo);
	initAddress(&pSupplier->address);
}

void getSupplierId(Supplier* pSupplier, Supplier** allSuppliers, int suppliersCount)
{
	int id;
	int flag = 1;
	do
	{
		printf("Enter unique Id:\t");
		scanf("%d",&id);
		for (int i = 0; i < suppliersCount; i++)
		{
			if (allSuppliers[i]->id == id)
				flag = 0;
		}
	} while (!flag);

	pSupplier->id = id;
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


