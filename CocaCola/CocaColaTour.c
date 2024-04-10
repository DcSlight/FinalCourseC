#include "CocaColaTour.h"

int initCocaColaTour(CocaColaTour* pTour, Employee* theGuide, char* fileName, const LIST* allEvents)
{
	int length = L_length(allEvents);
	if (!length)
	{
		printf("There is no events to present in the tour.\n");
		return 0;
	}
	printf("Initial a Tour:\n");
	if (!L_init(&pTour->events))
		return 0;
	initDateTime(&pTour->dateTime,0);
	int maxDuration;
	if (fileName)
	{
		maxDuration = getMaxDurationFromBFile(fileName);
		if (!maxDuration)
			return 0;
		getDuration(maxDuration, pTour);
		if (!fillEventsFromBFile(pTour, fileName, allEvents))//assumption: events are only in binary file.
			return 0;
	}
	else
	{
		maxDuration = length * EVENT_TIME;
		getDuration(maxDuration, pTour);
		if (!fillEventsFromFactory(pTour, allEvents))
			return 0;
	}
	printf("\nEnter visitor amount:\t");
	scanf("%u", &pTour->visitorAmount);
	printf("\n");
	pTour->guide = theGuide;
	return 1;
}

void getDuration(int maxDuration, CocaColaTour* pTour)
{
	int duration;
	do
	{
		printf("Enter duration from %d to %d:\t", EVENT_TIME, maxDuration);
		scanf("%u", &duration);
	} while (duration < EVENT_TIME || duration > maxDuration);
	pTour->duration = duration;
}

int getMaxDurationFromBFile(char* fileName)
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
	free(pTour);
}

void freeCocaColaTourPtr(void* pTourPtr)
{
	CocaColaTour* temp = *(CocaColaTour**)pTourPtr;
	freeCocaColaTour(temp);
}

void printCocaColaTour(const CocaColaTour* pTour)
{
	printf("Tour:\n");
	printDateTime(&pTour->dateTime);
	printEmployeeGuide(pTour->guide);
	printf("Duration: %u\n", pTour->duration);
	printf("Visitor Amount: %u\n", pTour->visitorAmount);
}

void printCocaColaTourPtr(void* pTourPtr)
{
	const CocaColaTour* temp = *(CocaColaTour**)pTourPtr;
	printCocaColaTour(temp);
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
int addRandomEvent(FILE* fp, int length, CocaColaTour* pTour,const LIST* allEvents)
{
	const NODE* pNodeFactory;
	int upper_bound = length-1;
	int lower_bound = 0;
	int index = rand() % (upper_bound - lower_bound + 1) + lower_bound;	
	if (fp)//from Binary file - using SEEK
	{
		HistoricalEvent* event = (HistoricalEvent*)malloc(sizeof(HistoricalEvent));//new
		if (!event)
			return 0;
		if (!getEventFromFileBySeek(fp, index, event))
		{
			freeHistoricalEvent(event);
			return 0;
		}
		pNodeFactory = L_find(allEvents->head.next, event, compareEventByDescription);
		if (!pNodeFactory)//check if exist in Factory events
		{
			freeHistoricalEvent(event);
			return 0;
		}
		const NODE* pNodeTour = L_find(pTour->events.head.next, event, compareEventByDescription);
		if (pNodeTour)//check if exist in Tour
		{
			freeHistoricalEvent(event);
			return 0;
		}
	}
	else
	{//from Factory event List
		pNodeFactory = L_find_By_Index(allEvents->head.next, index);
		if (!pNodeFactory)
		{
			return 0;
		}
		const NODE* pNodeTour = L_find(pTour->events.head.next, pNodeFactory->key, compareEventByDescription);
		if (pNodeTour)//check if exist in Tour
		{
			return 0;
		}
	}
	if(!L_insert_sorted(&pTour->events, pNodeFactory->key,compareEventByDateTime))//add event by dateTime
		return 0;
	return 1;
}


int fillEventsFromBFile(CocaColaTour* pTour, const char* fileName,const LIST* allEvents)
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

int fillEventsFromFactory(CocaColaTour* pTour,const LIST* allEvents)
{
	int eventsAmount = pTour->duration / EVENT_TIME;
	int i = 0;
	int maxEvents = L_length(allEvents);
	while (i < eventsAmount)
	{
		if (addRandomEvent(NULL, maxEvents, pTour, allEvents))
		{
			i++;
		}
	}
	return 1;
}


void startTour(CocaColaTour* pTour)
{
	printf(ANSI_COLOR_YELLOW "\n-----------------------------------\n" ANSI_COLOR_RESET);
	printf("Welcome to Coca Cola Tour\n");
	printf(ANSI_COLOR_YELLOW "-----------------------------------\n" ANSI_COLOR_RESET);
	printf("The Tour Guide is:\n");
	pTour->guide->print(pTour->guide);
	NODE* pNode = pTour->events.head.next;
	EmployeeGuide* pEmpGuideObj;
	pEmpGuideObj = pTour->guide->pDerivedObj;
	printf("The tour duration is: %d\n", pTour->duration);
	printf(ANSI_COLOR_YELLOW "-----------------------------------\n" ANSI_COLOR_RESET);
	while (pNode)
	{
		pEmpGuideObj->tellFact(pTour->guide,pNode->key);
		pNode = pNode->next;
	}
	printf("Thank you for listening.\n");
	printf(ANSI_COLOR_YELLOW "-----------------------------------\n" ANSI_COLOR_RESET);
}

int compareTourByDuration(const void* t1, const void* t2)
{
	const CocaColaTour* pTour1 = *(const CocaColaTour**)t1;
	const CocaColaTour* pTour2 = *(const CocaColaTour**)t2;
	if (pTour1->duration > pTour2->duration)
		return 1;
	if (pTour1->duration < pTour2->duration)
		return -1;
	return 0;
}

int compareTourByDateTime(const void* t1, const void* t2)
{
	const CocaColaTour* pTour1 = *(const CocaColaTour**)t1;
	const CocaColaTour* pTour2 = *(const CocaColaTour**)t2;
	return compareDateTime(&pTour1->dateTime, &pTour2->dateTime);
}

int compareTourByGuide(const void* t1, const void* t2)
{
	const CocaColaTour* pTour1 = *(const CocaColaTour**)t1;
	const CocaColaTour* pTour2 = *(const CocaColaTour**)t2;
	if (pTour1->guide->id > pTour2->guide->id)
		return 1;
	if (pTour1->guide->id < pTour2->guide->id)
		return -1;
	return 0;
}

int writeTourToBFile(FILE* fp, const CocaColaTour* pTour)
{
	if (!writeDateTimeToBFile(fp, &pTour->dateTime))
		return 0;
	if (!writeIntToFile(pTour->guide->id, fp, "Error writing guide id\n"))
		return 0;
	if (!writeIntToFile(pTour->duration, fp, "Error writing tour duration\n"))
		return 0;
	if (!writeIntToFile(pTour->visitorAmount, fp, "Error writing visitors amount\n"))
		return 0;

	return 1;
}

int readTourFromBFile(FILE* fp, CocaColaTour* pTour, int* guideId, const char* eventsFileName, LIST* allEvents)
{
	if (!readDateTimeFromBFile(fp, &pTour->dateTime))
		return 0;
	if (!readIntFromFile(guideId, fp, "Error reading guide id\n"))
		return 0;
	if (!readIntFromFile(&pTour->duration, fp, "Error reading tour duration\n"))
		return 0;
	if (!readIntFromFile(&pTour->visitorAmount, fp, "Error reading visitors amount\n"))
		return 0;
	//TODO: fill events from b file // filename is coca cola historical events file
	if (!fillEventsFromBFile(pTour, eventsFileName, allEvents))
		return 0;

	return 1;
}

int writeTourToTxtFile(FILE* fp, const CocaColaTour* pTour)
{
	if (!pTour)
		return 0;
	if (!writeDateTimeToTxtFile(fp, &pTour->dateTime))
		return 0;
	fprintf(fp, "%d\n", pTour->guide->id);
	fprintf(fp, "%d\n", pTour->duration);
	fprintf(fp, "%d\n", pTour->visitorAmount);
	return 1;
}

int readTourFromTxtFile(FILE* fp, CocaColaTour* pTour, int* guideId)
{
	if (!pTour)
		return 0;
	if (!readDateTimeFromTxtFile(fp, &pTour->dateTime))
		return 0;
	if (fscanf(fp, "%d", guideId) != 1)
		return 0;
	if (fscanf(fp, "%d", &pTour->duration) != 1)
		return 0;
	if (fscanf(fp, "%d", &pTour->visitorAmount) != 1)
		return 0;
	//TODO: fill events from b file // filename is coca cola historical events file

	return 1;
}
