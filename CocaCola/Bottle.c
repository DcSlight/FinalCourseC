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
	pBottle->sugar = getSugar();
	pBottle->calories = getCalories();
	pBottle->ml = getMl();
}

int getSugar()
{
	int sugar;
	do
	{
		printf("Enter sugar between %d and %d:\t", MIN_VALUE, MAX_SUGAR);
		scanf("%d", &sugar);
	} while (sugar > MAX_SUGAR || sugar < MIN_VALUE);
	return sugar;
}

int getCalories()
{
	int calories;
	do
	{
		printf("Enter calories between %d and %d:\t", MIN_VALUE, MAX_CALORIES);
		scanf("%d", &calories);
	} while (calories > MAX_CALORIES || calories < MIN_VALUE);
	return calories;
}

int getMl()
{
	int ml;
	do
	{
		printf("Enter ml between %d and %d:\t", MIN_VALUE, MAX_ML);
		scanf("%d", &ml);
	} while (ml > MAX_ML || ml < MIN_VALUE);
	return ml;
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
	printf("\nBottle details:\n");
	printf("Expiration ");
	printDateTime(&pBottle->expDate);
	printf("Flavor: %-10s\tType: %-7s\t", FlavorStr[pBottle->flavor], BottleStr[pBottle->type]);
	printf("Sugar: %-7d\tCalories: %-7d\tMl: %-7d\n", pBottle->sugar, pBottle->calories, pBottle->ml);
}

int writeBottleToTxtFile(FILE* fp, const Bottle* pBottle)
{
	if (!writeDateTimeToTxtFile(fp, &pBottle->expDate))
		return 0;
	fprintf(fp, "%d\n", pBottle->flavor);
	fprintf(fp, "%d\n", pBottle->type);
	fprintf(fp, "%d\n", pBottle->sugar);
	fprintf(fp, "%d\n", pBottle->calories);
	fprintf(fp, "%d\n", pBottle->ml);
	return 1;
}

int readBottleFromTxtFile(FILE* fp, Bottle* pBottle)
{
	if (!readDateTimeFromTxtFile(fp, &pBottle->expDate))
		return 0;
	if (fscanf(fp, "%d", &pBottle->flavor) != 1)
		return 0;
	if (fscanf(fp, "%d", &pBottle->type) != 1)
		return 0;
	if (fscanf(fp, "%d", &pBottle->sugar) != 1)
		return 0;
	if (fscanf(fp, "%d", &pBottle->calories) != 1)
		return 0;
	if (fscanf(fp, "%d", &pBottle->ml) != 1)
		return 0;
	return 1;
}

int writeBottleToBFileCompress(FILE* fp, const Bottle* pBottle)
{
	BYTE data[4];
	data[0] = pBottle->flavor << 6;
	data[0] |= pBottle->type << 4;
	data[0] |= (pBottle->sugar >> 3);
	data[1] = pBottle->sugar << 5;
	data[1] |= pBottle->calories >> 5;
	data[2] = pBottle->calories << 3;
	data[2] |= pBottle->ml >> 8;
	data[3] = pBottle->ml;
	if (fwrite(data, sizeof(BYTE), 4, fp) != 4)
		return 0;
	if(!writeDateTimeToBFile(fp,&pBottle->expDate))
		return 0;
	return 1;
}

int readBottleFromBFileCompress(FILE* fp, Bottle* pBottle)
{
	BYTE data[4];
	if (fread(data, sizeof(BYTE), 4, fp) != 4)
		return 0;
	pBottle->flavor = data[0] >> 6;
	pBottle->type = (data[0] >> 4) & 0x3;
	pBottle->sugar = ((data[0] & 0xF)<<3) | (data[1] >> 5);
	pBottle->calories = ((data[1] & 0x1F)<<5) | (data[2] >> 3);
	pBottle->ml = ((data[2] & 0x7)<<8) | (data[3]);
	if (!readDateTimeFromBFile(fp, &pBottle->expDate))
		return 0;
	return 1;
}
