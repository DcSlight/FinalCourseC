#ifndef __BOTTLE__
#define __BOTTLE__

#include "DateTime.h"

typedef enum {
	eClassic, eZero, eLemon, eNonCaffein, eNofFlavorTypes
} eFlavorType;

static const char* FlavorStr[eNofFlavorTypes];

typedef enum {
	ePlastic, eGlass, eCan, eNofBottleTypes
} eBottleType;

static const char* BottleStr[eNofBottleTypes];

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
eFlavorType getFlavorType();
eBottleType getBottleType();
void printBottle(const Bottle* pBottle);


#endif /* __BOTTLE__ */