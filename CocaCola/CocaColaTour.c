#include "CocaColaTour.h"

int initCocaColaTour(CocaColaTour* pTour,char* fileName)
{
	printf("Initial a Tour:\n");
	if (!L_init(&pTour->events))
		return 0;
	initDateTime(&pTour->dateTime);
	if (!getDuration(pTour, fileName))
		return 0;
	printf("\nEnter visitor amount:\t");
	scanf("%u", &pTour->visitorAmount);
	printf("\n");
	initEmployeeGuide(&pTour->guide); //TODO: need to get from array
	return 1;
}

int getDuration(CocaColaTour* pTour, char* fileName)
{
	int maxDuration = getMaxDuration(fileName);
	if (!maxDuration)
	{
		freeCocaColaTour(pTour);
		return 0;
	}
	int duration;
	do
	{
		printf("Enter duration from %d to %d:\t", EVENT_TIME, maxDuration);
		scanf("%u", &duration);
	} while (duration < EVENT_TIME || duration > maxDuration);
	pTour->duration = duration;
	return 1;
}

int getMaxDuration(char* fileName)
{
	FILE* fp = fopen(fileName, "rb");
	if (!fp)
		return 0;
	int numOfEvents;
	if (!readIntFromFile(&numOfEvents, fp, "Error reading num of events"))
	{
		fclose(fp);
		return 0;
	}
	return numOfEvents*EVENT_TIME;
}

void freeCocaColaTour(CocaColaTour* pTour)
{
	L_free(&pTour->events,NULL);//free only the NODES, we don't want to free Factory data
	pTour->guide->delete(pTour->guide);
}

void printCocaColaTour(const CocaColaTour* pTour)
{
	printf("Tour:\n");
	printDateTime(&pTour->dateTime);
	printEmployeeGuide(pTour->guide);
	printf("Duration: %u\n", pTour->duration);
	printf("Visitor Amount: %u\n", pTour->visitorAmount);
}

int getEventFromFileBySeek(FILE* fp, int index, HistoricalEvent* pEvent)
{
	long offset = sizeof(int);//firstInt
	int stringLength;
	for (int i = 0; i < index; i++)
	{
		offset += sizeof(Time) + sizeof(Date);//jump over DateTime
		fseek(fp, offset, SEEK_SET);
		if (!readIntFromFile(&stringLength, fp, "error")) //read description length
			return 0;
		offset += sizeof(int) + stringLength * sizeof(char); //jump over the description event
	}
	fseek(fp, offset, SEEK_SET);
	if (!readEventFromBFile(fp,pEvent))
		return 0;
	return 1;
}

/*
* This function will random event from the bin file.
* We ensure that there is no duplication of the same event.
* The Tour have the same key pointer as the Factory to specific event.
*/
int addRandomEvent(FILE* fp, int length, CocaColaTour* pTour, LIST allEvents)
{
	int upper_bound = length-1;
	int lower_bound = 0;
	int index = rand() % (upper_bound - lower_bound + 1) + lower_bound;	
	HistoricalEvent* event = (HistoricalEvent*)malloc(sizeof(HistoricalEvent));
	if (!event)
		return 0;
	if (!getEventFromFileBySeek(fp, index, event))
	{
		freeHistoricalEvent(event);
		return 0;
	}

	const NODE* pNodeTour = L_find(pTour->events.head.next, event, compareEventByDescription);
	if (pNodeTour)//exist
	{
		freeHistoricalEvent(event);
		return 0;
	}

	const NODE* pNodeFactory = L_find(allEvents.head.next, event, compareEventByDescription);
	if (!pNodeFactory)
	{
		freeHistoricalEvent(event);
		return 0;
	}
	freeHistoricalEvent(event);
	if(!L_insert_sorted(&pTour->events, pNodeFactory->key,compareEventByDateTime))//add event by dateTime
		return 0;
	return 1;
}

int fillEvents(CocaColaTour* pTour,char* fileName, LIST allEvents)
{
	int eventsAmount = pTour->duration / EVENT_TIME;
	int i = 0;
	FILE* fp = fopen(fileName, "rb");
	if (!fp)
	{
		perror("Error opening file");
		return 1;
	}
	int maxEvents;
	if (!readIntFromFile(&maxEvents, fp, "Error reading num of events"))
	{
		fclose(fp);
		return 0;
	}
	while (i < eventsAmount)
	{
		if (addRandomEvent(fp, maxEvents, pTour, allEvents))
		{
			i++;
		}
	}
	fclose(fp);
	return 1;
}

void startTour(CocaColaTour* pTour)
{
	printf("Welcome to Coca Cola Tour\n");
	printf("The Tour Guide is:\n");
	pTour->guide->print(pTour->guide);
	NODE* pNode = pTour->events.head.next;
	EmployeeGuide* pEmpGuideObj;
	pEmpGuideObj = pTour->guide->pDerivedObj;
	printf("The tour duration is: %d\n", pTour->duration);
	while (pNode)
	{
		pEmpGuideObj->tellFact(pTour->guide,pNode->key);
		pNode = pNode->next;
	}
	printf("Thank you for listening.\n");
}

int compareTourByDuration(const void* t1, const void* t2)
{
	const CocaColaTour* pTour1 = (const CocaColaTour*)t1;
	const CocaColaTour* pTour2 = (const CocaColaTour*)t2;
	if (pTour1->duration > pTour2->duration)
		return 1;
	if (pTour1->duration < pTour2->duration)
		return -1;
	return 0;
}

int compareTourByDateTime(const void* t1, const void* t2)
{
	const CocaColaTour* pTour1 = (const CocaColaTour*)t1;
	const CocaColaTour* pTour2 = (const CocaColaTour*)t2;
	return compareDateTime(&pTour1->dateTime, &pTour2->dateTime);
}
