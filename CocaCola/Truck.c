#include "Truck.h"

int initTruck(Truck* pTruck, Supplier* theSupplier, Employee* theDriver)
{
	getLicenseCode(pTruck->truckLicenseCode);
	printf("\n");
	pTruck->driver = theDriver;
	pTruck->destSupplier = theSupplier;
	pTruck->packAmount = 0;
	return 1;
}

void getLicenseCode(char* code)
{
	char temp[MAX_STR_LEN];
	int ok = 1;
	do {
		ok = 1;
		printf("Enter truck license code  - %d UPPER CASE letters or numbers\t", LICENSE_LEN); //TODO: need to be unique
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


int writeTruckToBFile(FILE* fp, const Truck* pTruck)
{
	if (!writeCharsToFile(pTruck->truckLicenseCode, LICENSE_LEN+1, fp, "Error Writing Truck License\n"))
		return 0;
	if (!writeIntToFile(pTruck->destSupplier->id, fp, "Error Writing Supplier Id\n"))
		return 0;
	if (!writeIntToFile(pTruck->driver->id, fp, "Error Writing Driver Id\n"))
		return 0;
	if (!writeIntToFile(pTruck->packAmount, fp, "Error Writing Packs Amount\n"))
		return 0;
	for (int i = 0; i < pTruck->packAmount; i++)
	{
		if (!writeBottlePackingToBFile(fp, &pTruck->packs[i]))
			return 0;
	}
	return 1;
}

int readTruckFromBFile(FILE* fp, Truck* pTruck, int* supplierId, int* driverId)
{
	if (!readCharsFromFile(pTruck->truckLicenseCode, LICENSE_LEN+1, fp, "Error reading truck license\n"))
		return 0;
	if (!readIntFromFile(supplierId, fp, "Error reading supplier id\n"))
		return 0;
	if (!readIntFromFile(driverId, fp, "Error reading driver id\n"))
		return 0;
	if (!readIntFromFile(&pTruck->packAmount, fp, "Error reading packs amount\n"))
		return 0;
	for (int i = 0; i < pTruck->packAmount; i++)
	{
		if (!readBottlePackingFromBFile(fp, &pTruck->packs[i]))
			return 0;
	}
	
	return 1;
}

int writeTruckToTxtFile(FILE* fp, const Truck* pTruck)
{
	if (!pTruck)
		return 0;
	fprintf(fp, "%s\n", pTruck->truckLicenseCode);
	fprintf(fp, "%d\n", pTruck->driver->id);
	fprintf(fp, "%d\n", pTruck->destSupplier->id);
	fprintf(fp, "%d\n", pTruck->packAmount);
	for (int i = 0; i < pTruck->packAmount; i++)
	{
		if (!writeBottlePackingToTxtFile(fp, &pTruck->packs[i]))
			return 0;
	}
	return 1;
}

int readTruckFromTxtFile(FILE* fp, Truck* pTruck, int* supplierId, int* driverId)
{
	myGets(pTruck->truckLicenseCode, LICENSE_LEN + 1, fp); //TODO: check

	if (fscanf(fp, "%d", driverId) != 1)
		return 0;
	if (fscanf(fp, "%d", supplierId) != 1)
		return 0;
	if (fscanf(fp, "%d", &pTruck->packAmount) != 1)
		return 0;
	for (int i = 0; i < pTruck->packAmount; i++)
	{
		if (!readBottlePackingFromTxtFile(fp, &pTruck->packs[i]))
			return 0;
	}
	return 1;
}
