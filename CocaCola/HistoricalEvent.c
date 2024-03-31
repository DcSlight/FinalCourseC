#include "HistoricalEvent.h"

void initHistoricalEvent(HistoricalEvent* pHistory)
{
	printf("Enter historical event\n");
	initDateTime(&pHistory->eventDate);
	pHistory->description = getStrExactName("Enter a description:");
}

void printHistoricalEvent(const HistoricalEvent* pHistory)
{
	printf("Event:\n");
	printDateTime(&pHistory->eventDate);
	printf("Description: %s\n",pHistory->description);
}

void freeHistoricalEvent(HistoricalEvent* pHistory)
{
	free(pHistory->description);
}

int writeEventToBFile(FILE* fp,const HistoricalEvent* pHistory)
{
	//TODO: DateTime
	/*if (!writeStringToFile(fp, pComp))
	{
		return 0;
	}*/
	if (!writeStringToFile(pHistory->description,fp,"Error Writing History Description\n"))
	{
		return 0;
	}
	return 1;
}

int writeEventToTxtFile(FILE* fp, const HistoricalEvent* pHistory)
{
	if (!pHistory)
		return 0;
	writeDateTimeToTxtFile(fp, &pHistory->eventDate);
	fprintf(fp, "%s\n", pHistory->description);
	return 1;
}


