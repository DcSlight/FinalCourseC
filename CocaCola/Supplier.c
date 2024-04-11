#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Supplier.h"
#include "General.h"

void initSupplier(Supplier* pSupplier, Supplier** allSuppliers,int suppliersCount)
{
	getSupplierId(pSupplier, allSuppliers, suppliersCount);
	pSupplier->name = getStrExactName("Enter supplier name:");
	getSupplierPhone(pSupplier->phoneNo);
	initAddress(&pSupplier->address);
}

void getSupplierId(Supplier* pSupplier, Supplier** allSuppliers, int suppliersCount)
{
	int id;
	int flag;
	do
	{
		printf("Enter unique Id:\t");
		scanf("%d",&id);
		flag = 1;
		for (int i = 0; i < suppliersCount; i++)
		{
			if (allSuppliers[i]->id == id)
			{
				flag = 0;
				break;
			}
		}
	} while (!flag);

	pSupplier->id = id;
}

void getSupplierPhone(char* phoneNumber)
{
	char temp[MAX_STR_LEN];
	int ok = 1;
	do {
		ok = 1;
		printf("Enter a phone number - %d digits:\t", PHONE_LEN);
		myGets(temp, MAX_STR_LEN, stdin);
		if (strlen(temp) != PHONE_LEN)
		{
			printf("code should be %d digits\n", PHONE_LEN);
			ok = 0;
		}
		else {
			for (int i = 0; i < PHONE_LEN; i++)
			{
				if (isdigit(temp[i]) == 0)
				{
					printf("Need to be upper digits\n");
					ok = 0;
					break;
				}
			}
		}
	} while (!ok);
	strcpy(phoneNumber, temp);
	
}

void printSupplier(const Supplier* pSupplier)
{
	printf("ID: %-15d\t", pSupplier->id);
	printf("Name: %-15s\t", pSupplier->name);
	printf("Phone No: %-15s\t", pSupplier->phoneNo);
	printAddress(&pSupplier->address);
}

void printSupplierPtr(void* pSupplierPtr)
{
	const Supplier* temp = *(Supplier**)pSupplierPtr;
	printSupplier(temp);
}

void freeSupplier(Supplier* pSupplier)
{
	free(pSupplier->name);
	freeAddress(&pSupplier->address);
	free(pSupplier);
}

void freeSupplierPtr(void* pSupplierPtr)
{
	Supplier* temp = *(Supplier**)pSupplierPtr;
	freeSupplier(temp);
}

int writeSupplierToBFile(FILE* fp, const Supplier* pSupplier)
{
	if (!writeIntToFile(pSupplier->id, fp, "Error Writing Supplier Id\n"))
		return 0;
	if (!writeStringToFile(pSupplier->name, fp, "Error Writing Supplier Name\n"))
		return 0;
	if (!writeCharsToFile(pSupplier->phoneNo, PHONE_LEN, fp, "Error Writing Phone Number\n"))
		return 0;
	if (!writeAddressToBFile(fp, &pSupplier->address))
		return 0;

	return 1;
}

int readSupplierFromBFile(FILE* fp, Supplier* pSupplier)
{
	if (!readIntFromFile(&pSupplier->id, fp, "Error reading supplier id\n"))
		return 0;
	pSupplier->name = readStringFromFile(fp, "Error reading supplier name\n");
	if (!pSupplier->name)
		return 0;
	if (!readCharsFromFile(pSupplier->phoneNo, PHONE_LEN, fp, "Error reading supplier phone number\n"))
		return 0;
	if (!readAddressFromBFile(fp, &pSupplier->address))
		return 0;

	return 1;
}

int writeSupplierToTxtFile(FILE* fp, const Supplier* pSupplier)
{
	if (!pSupplier)
		return 0;
	fprintf(fp, "%d\n", pSupplier->id);
	fprintf(fp, "%s\n", pSupplier->name);
	fprintf(fp, "%s\n", pSupplier->phoneNo);
	if (!writeAddressToTxtFile(fp, &pSupplier->address))
		return 0;
	return 1;
}

int readSupplierFromTxtFile(FILE* fp, Supplier* pSupplier)
{
	char temp[MAX_STR_LEN];
	if (!pSupplier)
		return 0;

	int tempId;
	if (fscanf(fp, "%d", &tempId) != 1)
		return 0;
	pSupplier->id = tempId;

	myGets(temp, MAX_STR_LEN, fp);
	pSupplier->name = getDynStr(temp);

	myGets(pSupplier->phoneNo, PHONE_LEN+1, fp);
	
	if (!readAddressFromTxtFile(fp, &pSupplier->address))
		return 0;

	return 1;
}


