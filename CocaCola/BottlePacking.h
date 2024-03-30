#ifndef __BOTTLE_PACKING__
#define __BOTTLE_PACKING__

#include "Bottle.h"

typedef struct
{
	Bottle bottle;
	int quantity;
} BottlePacking;

void initBottlePacking(BottlePacking* pBottlePack);
void printBottlePacking(BottlePacking* pBottlePack);

#endif /* __BOTTLE_PACKING__ */
