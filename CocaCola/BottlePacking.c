#include <stdio.h>
#include "BottlePacking.h"

void initBottlePacking(BottlePacking* pBottlePack)
{
	printf("Fill up the bottle details in the pack\n");
	initBottle(&pBottlePack->bottle);
	printf("\nHow many bottles in the pack?\t");
	scanf("%d", &pBottlePack->quantity);
	printf("\n");
}

void printBottlePacking(const BottlePacking* pBottlePack)
{
	printf("In the pack there are %d bottles\n", pBottlePack->quantity);
	printBottle(&pBottlePack->bottle);
}

int writeBottlePackingToBFile(FILE* fp, const BottlePacking* pBottlePacking)
{
	if (!writeBottleToBFileCompress(fp, &pBottlePacking->bottle))
		return 0;
	if (!writeIntToFile(pBottlePacking->quantity, fp, "Error Writing Bottle Quantity\n"))
		return 0;

	return 1;
}

int readBottlePackingFromBFile(FILE* fp, BottlePacking* pBottlePacking)
{
	if (!readBottleFromBFileCompress(fp, &pBottlePacking->bottle))
		return 0;
	if (!readIntFromFile(&pBottlePacking->quantity, fp, "Error reading bottle quantity\n"))
		return 0;

	return 1;
}

int writeBottlePackingToTxtFile(FILE* fp, const BottlePacking* pBottlePacking)
{
	if (!writeBottleToTxtFile(fp, &pBottlePacking->bottle))
		return 0;
	fprintf(fp, "%d\n", pBottlePacking->quantity);
	return 1;
}

int readBottlePackingFromTxtFile(FILE* fp, BottlePacking* pBottlePacking)
{
	if (!readBottleFromTxtFile(fp, &pBottlePacking->bottle))
		return 0;
	if (fscanf(fp, "%d", &pBottlePacking->quantity) != 1)
		return 0;
	return 1;
}


