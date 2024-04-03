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
	//TODO: write Bottle compressed
	if (!writeIntToFile(pBottlePacking->quantity, fp, "Error Writing Bottle Quantity\n"))
	{
		fclose(fp);
		return 0;
	}
	return 1;
}

int readBottlePackingFromBFile(FILE* fp, BottlePacking* pBottlePacking)
{
	//TODO: read bottle compressed
	if (!readIntFromFile(&pBottlePacking->quantity, fp, "Error reading bottle quantity\n"))
	{
		fclose(fp);
		return 0;
	}
	return 1;
}


