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

void printBottlePacking(BottlePacking* pBottlePack)
{
	printf("In the pack there are %d bottles\n", pBottlePack->quantity);
	printBottle(&pBottlePack->bottle);
}


