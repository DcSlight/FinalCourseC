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
#include "CocaColaFunctions.h"


#define EVENT_TIME 10

typedef struct
{
	DateTime dateTime;
	LIST events;
	unsigned duration;
	Employee* guide;
	unsigned visitorAmount;
} CocaColaTour;

int initCocaColaTour(CocaColaTour* pTour, Employee* theGuide, char* fileName,const LIST* allEvents);
int getMaxDurationFromBFile(char* fileName);
void getDuration(int maxDuration, CocaColaTour* pTour);

void freeCocaColaTour(CocaColaTour* pTour);
void freeCocaColaTourPtr(void* pTourPtr);

void printCocaColaTour(const CocaColaTour* pTour);
void printCocaColaTourPtr(void* pTourPtr);
int getEventFromFileBySeek(FILE* fp, int index, HistoricalEvent* pEvent);
int addRandomEvent(FILE* fp, int length, CocaColaTour* pTour,const LIST* allEvents);
int fillEventsFromBFile(CocaColaTour* pTour, const char* fileName,const LIST* allEvents);
int fillEventsFromFactory(CocaColaTour* pTour,const LIST* allEvents);
void startTour(CocaColaTour* pTour);
int	compareTourByDuration(const void* t1, const void* t2);
int	compareTourByDateTime(const void* t1, const void* t2);
int	compareTourByGuide(const void* t1, const void* t2);

int writeTourToBFile(FILE* fp, const CocaColaTour* pTour);
int readTourFromBFile(FILE* fp, CocaColaTour* pTour, int* guideId, const char* eventsFileName, LIST* allEvents);

int writeTourToTxtFile(FILE* fp, const CocaColaTour* pTour);
int readTourFromTxtFile(FILE* fp, CocaColaTour* pTour, int* guideId, const LIST* allEvents);


#endif
