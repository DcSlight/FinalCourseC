#ifndef __HISTORICAL_EVENTS__
#define __HISTORICAL_EVENTS__

#include <stdio.h>
#include <stdlib.h>
#include "DateTime.h"
#include "General.h"
#include "FileHelper.h"

#define MIN_HISTORY_YEAR 1886 //date of inventing CocaCola Formula

typedef struct
{
	DateTime eventDate;
	char* description;
} HistoricalEvent;

void initHistoricalEvent(HistoricalEvent* pHistory);
void printHistoricalEvent(const HistoricalEvent* pHistory);
void freeHistoricalEvent(const void* val);

int writeEventToBFile(FILE* fp, const HistoricalEvent* pHistory);
int writeEventToTxtFile(FILE* fp, const HistoricalEvent* pHistory);

int readEventFromBFile(FILE* fp, HistoricalEvent* pHistory);
int readEventFromTxtFile(FILE* fp, HistoricalEvent* pHistory);


int compareEventByDateTime(const void* e1, const void* e2);
int compareEventByDescription(const void* e1, const void* e2);
#endif
