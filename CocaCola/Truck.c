#include "Truck.h"

int initTruck(Truck* pTruck)
{
	Supplier* pSupplier = (Supplier*)malloc(sizeof(Supplier));
	if (!pSupplier)
	{
		printf("Error allocation\n");
		return 0;
	}
	getLicenseCode(pTruck->truckLicenseCode);
	printf("\n");
	initEmployeeDriver(&pTruck->driver);
	initSupplier(pSupplier);
	pTruck->destSupplier = pSupplier;
	pTruck->packAmount = 0;
	return 1;
}

void getLicenseCode(char* code)
{
	char temp[MAX_STR_LEN];
	int ok = 1;
	do {
		ok = 1;
		printf("Enter truck license code  - %d UPPER CASE letters or numbers\t", LICENSE_LEN);
		myGets(temp, MAX_STR_LEN, stdin);
		if (strlen(temp) != LICENSE_LEN)
		{
			printf("code should be %d letters or numbers\n", LICENSE_LEN);
			ok = 0;
		}
		else {
			for (int i = 0; i < LICENSE_LEN; i++)
			{
				if (isupper(temp[i]) == 0 && isdigit(temp[i]) == 0)
				{
					printf("Need to be upper case letter or numbers\n");
					ok = 0;
					break;
				}
			}
		}
	} while (!ok);
	strcpy(code, temp);
}

int addPack(Truck* pTruck)
{
	if (pTruck->packAmount >= MAX_PACKS)
	{
		printf("Error adding packs, Truck is full\n");
		return 0;
	}
	initBottlePacking(&pTruck->packs[pTruck->packAmount]);
	pTruck->packAmount++;
	return 1;
}

void printTruck(const Truck* pTruck)
{
	printf("\nTruck License: %s\n", pTruck->truckLicenseCode);
	printf("\nDriver:\n");
	pTruck->driver->print(pTruck->driver);
	printf("\n");
	printSupplier(pTruck->destSupplier);
	printf("\n");
	printf("The truck has %d packs of Coca Cola bottles\n\n", pTruck->packAmount);
}

void printTruckContent(const Truck* pTruck)
{
	printf("The truck has %d packs of Coca Cola bottles\n", pTruck->packAmount);
	for (int i = 0; i < pTruck->packAmount; i++)
	{
		printf("\nPack %d\n", i+1);
		printBottlePacking(&pTruck->packs[i]);
		printf("\n");
	}
}

void freeTruck(Truck* pTruck)
{
	pTruck->driver->delete(pTruck->driver);
	freeSupplier(pTruck->destSupplier);
	free(pTruck->destSupplier);
}
