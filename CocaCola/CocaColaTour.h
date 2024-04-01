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


#define EVENT_TIME 10

typedef struct
{
	DateTime dateTime;
	LIST events;
	unsigned duration;
	Employee* guide;
	unsigned visitorAmount;
} CocaColaTour;

int initCocaColaTour(CocaColaTour* pTour, char* fileName);
int getMaxDuration(char* fileName);
int getDuration(CocaColaTour* pTour, char* fileName);
void freeCocaColaTour(CocaColaTour* pTour);
void printCocaColaTour(const CocaColaTour* pTour);
int getEventFromFileBySeek(FILE* fp, int index, HistoricalEvent* pEvent);
int addRandomEvent(FILE* fp, int length, CocaColaTour* pTour);
int fillEvents(CocaColaTour* pTour, char* fileName);
void startTour(CocaColaTour* pTour);
int	compareTourByDuration(const void* t1, const void* t2);
int	compareTourByDateTime(const void* t1, const void* t2);

#endif
