#ifndef __HISTORICAL_EVENTS__
#define __HISTORICAL_EVENTS__

#include <stdio.h>
#include <stdlib.h>
#include "DateTime.h"
#include "General.h"
#include "FileHelper.h"

typedef struct
{
	DateTime eventDate;
	char* description;
	
} HistoricalEvent;

void initHistoricalEvent(HistoricalEvent* pHistory);
void printHistoricalEvent(const HistoricalEvent* pHistory);
void freeHistoricalEvent(HistoricalEvent* pHistory);

int writeEventToBFile(FILE* fp, const HistoricalEvent* pHistory);
int writeEventToTxtFile(FILE* fp, const HistoricalEvent* pHistory);

int readEventFromTxtFile(FILE* fp, HistoricalEvent* pHistory);

#endif
