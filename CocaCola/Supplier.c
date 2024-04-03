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

int writeSupplierToBFile(FILE* fp, const Supplier* pSupplier)
{
	if (!writeIntToFile(pSupplier->id, fp, "Error Writing Supplier Id\n"))
	{
		fclose(fp);
		return 0;
	}
	if (!writeStringToFile(pSupplier->name, fp, "Error Writing Supploer Name\n"))
	{
		fclose(fp);
		return 0;
	}
	if (!writeCharsToFile(pSupplier->phoneNo, PHONE_LEN, fp, "Error Writing Phone Number\n"))
	{
		fclose(fp);
		return 0;
	}
	if (!writeAddressToBFile(fp, &pSupplier->address))
	{
		fclose(fp);
		return 0;
	}
	return 1;
}

int readSupplierFromBFile(FILE* fp, Supplier* pSupplier)
{
	if (!readIntFromFile(&pSupplier->id, fp, "Error reading supplier id\n"))
	{
		fclose(fp);
		return 0;
	}
	pSupplier->name = readStringFromFile(fp, "Error reading supplier name\n");
	if (!pSupplier->name)
	{
		fclose(fp);
		return 0;
	}
	if (!readCharsFromFile(pSupplier->phoneNo, PHONE_LEN, fp, "Error reading supplier phone number\n"))
	{
		fclose(fp);
		return 0;
	}
	if (!readAddressFromBFile(fp, &pSupplier->address))
	{
		fclose(fp);
		return 0;
	}
	return 1;
}


