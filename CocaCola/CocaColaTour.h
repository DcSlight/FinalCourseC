#ifndef __TOUR__
#define __TOUR__

#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "General.h"
#include "Employee.h"
#include "HistoricalEvent.h"
#include "GuideEmployee.h"
#include "DateTime.h"

typedef struct
{
	DateTime dateTime;
	LIST events;
	unsigned duration;
	Employee* guide;
	unsigned visitorAmount;
} CocaColaTour;

int initCocaColaTour(CocaColaTour* pTour);
void freeCocaColaTour(const CocaColaTour* pTour);
void printCocaColaTour(const CocaColaTour* pTour);

#endif
