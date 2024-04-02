#include "HistoricalEvent.h"

void initHistoricalEvent(HistoricalEvent* pHistory)
{
	printf("Enter historical event\n");
	initDateTime(&pHistory->eventDate,MIN_HISTORY_YEAR);
	pHistory->description = getStrExactName("Enter a description:");
}

void printHistoricalEvent(const HistoricalEvent* pHistory)
{
	printf("Event:\n");
	printDateTime(&pHistory->eventDate);
	printf("Description: %s\n", pHistory->description);
}

void freeHistoricalEvent(const void* val)
{
	HistoricalEvent* e = (HistoricalEvent*)val;
	free(e);
}

int writeEventToBFile(FILE* fp, const HistoricalEvent* pHistory)
{
	if (!writeDateTimeToBFile(fp, &pHistory->eventDate))
	{
		fclose(fp);
		return 0;
	}
	if (!writeStringToFile(pHistory->description, fp, "Error Writing History Description\n"))
	{
		fclose(fp);
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

int readEventFromBFile(FILE* fp, HistoricalEvent* pHistory)
{
	if (!readDateTimeFromBFile(fp, &pHistory->eventDate))
	{
		fclose(fp);
		return 0;
	}
	pHistory->description = readStringFromFile(fp, "Error reading event description\n");
	if (!pHistory->description)
	{
		fclose(fp);
		return 0;
	}
	return 1;
}

int readEventFromTxtFile(FILE* fp, HistoricalEvent* pHistory)
{
	char temp[MAX_STR_LEN];
	if (!pHistory)
		return 0;

	readDateTimeFromTxtFile(fp, &pHistory->eventDate);
	myGets(temp, MAX_STR_LEN, fp);
	pHistory->description = getDynStr(temp);
	return 1;
}

int compareEventByDateTime(const void* e1, const void* e2)
{
	const HistoricalEvent* pEvent1 = (const HistoricalEvent*)e1;
	const HistoricalEvent* pEvent2 = (const HistoricalEvent*)e2;
	return compareDateTime(&pEvent1->eventDate, &pEvent2->eventDate);
}


int compareEventByDescription(const void* e1, const void* e2)
{
	const HistoricalEvent* pEvent1 = (const HistoricalEvent*)e1;
	const HistoricalEvent* pEvent2 = (const HistoricalEvent*)e2;
	return strcmp(pEvent1->description, pEvent2->description);
}


