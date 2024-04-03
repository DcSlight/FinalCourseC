#ifndef __BOTTLE_PACKING__
#define __BOTTLE_PACKING__

#include "Bottle.h"
#include "FileHelper.h"

typedef struct
{
	Bottle bottle;
	int quantity;
} BottlePacking;

void initBottlePacking(BottlePacking* pBottlePack);
void printBottlePacking(const BottlePacking* pBottlePack);

int writeBottlePackingToBFile(FILE* fp, const BottlePacking* pBottlePacking);
int readBottlePackingFromBFile(FILE* fp, BottlePacking* pBottlePacking);

#endif /* __BOTTLE_PACKING__ */
