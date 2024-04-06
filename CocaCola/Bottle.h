#ifndef __BOTTLE__
#define __BOTTLE__

#include "DateTime.h"
#include "General.h"

typedef enum {
	eClassic, eZero, eLemon, eNonCaffein, eNofFlavorTypes
} eFlavorType;

static const char* FlavorStr[eNofFlavorTypes];

typedef enum {
	ePlastic, eGlass, eCan, eNofBottleTypes
} eBottleType;

static const char* BottleStr[eNofBottleTypes];

typedef unsigned char BYTE;

#define MIN_VALUE 0
#define MAX_SUGAR 127
#define MAX_CALORIES 1023
#define MAX_ML 2000

typedef struct
{
	DateTime expDate;
	eFlavorType flavor;
	eBottleType type;
	int sugar;
	int calories;
	int ml;
} Bottle;

void initBottle(Bottle* pBottle);
int getSugar();
int getCalories();
int getMl();
eFlavorType getFlavorType();
eBottleType getBottleType();
void printBottle(const Bottle* pBottle);

int writeBottleToTxtFile(FILE* fp, const Bottle* pBottle);
int readBottleFromTxtFile(FILE* fp, Bottle* pBottle);

int writeBottleToBFileCompress(FILE* fp, const Bottle* pBottle);
int readBottleFromBFileCompress(FILE* fp, Bottle* pBottle);

#endif /* __BOTTLE__ */