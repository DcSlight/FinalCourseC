#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Bottle.h"
#include "DateTime.h"

static const char* FlavorStr[eNofFlavorTypes] 
	= { "Classic", "Zero", "Lemon", "NonCaffein" };

static const char* BottleStr[eNofBottleTypes]
	= { "Plastic", "Glass", "Can" };

void initBottle(Bottle* pBottle)
{
	pBottle->flavor = getFlavorType();
	pBottle->type = getBottleType();
	printf("Enter expiration date and time of the bottle\n");
	initDateTime(&pBottle->expDate,0);
	printf("Enter sugar, calories and ml\n");
	scanf("%d%d%d", &pBottle->sugar, &pBottle->calories, &pBottle->ml);
}

eFlavorType getFlavorType()
{
	int option;
	do {
		printf("Please enter one of the following types\n");
		for (int i = 0; i < eNofFlavorTypes; i++)
			printf("%d for %s\n", i, FlavorStr[i]);
		scanf("%d", &option);
	} while (option < 0 || option >= eNofFlavorTypes);
	getchar();
	return (eFlavorType)option;
}

eBottleType getBottleType()
{
	int option;
	do {
		printf("Please enter one of the following types\n");
		for (int i = 0; i < eNofBottleTypes; i++)
			printf("%d for %s\n", i, BottleStr[i]);
		scanf("%d", &option);
	} while (option < 0 || option >= eNofBottleTypes);
	getchar();
	return (eBottleType)option;
}

void printBottle(const Bottle* pBottle)
{
	printf("Bottle details:\n");
	printf("Flavor: %s\nType: %s\n", FlavorStr[pBottle->flavor], BottleStr[pBottle->type]);
	printf("Expiration: ");
	printDateTime(&pBottle->expDate);
	printf("Sugar: %d\nCalories: %d\nMl: %d\n", pBottle->sugar, pBottle->calories, pBottle->ml);
}
