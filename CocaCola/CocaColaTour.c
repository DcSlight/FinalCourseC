#include "CocaColaTour.h"

int initCocaColaTour(CocaColaTour* pTour)
{
	printf("Initial a Tour:\n");
	if (!L_init(&pTour->events))
		return 0;
	initDateTime(&pTour->dateTime);
	printf("Enter duration:\t");
	scanf("%u", &pTour->duration);
	printf("\nEnter visitor amount:\t");
	scanf("%u", &pTour->visitorAmount);
	printf("\n");
	initEmployeeGuide(&pTour->guide); //TODO: need to get from array
	return 1;
}

void freeCocaColaTour(CocaColaTour* pTour)
{
	L_free(&pTour->events, freeHistoricalEvent);
	pTour->guide->delete(pTour->guide);
}

void printCocaColaTour(const CocaColaTour* pTour)
{
	printf("Tour:\n");
	printDateTime(&pTour->dateTime);
	printEmployeeGuide(pTour->guide);
	printf("Duration: %u\n", pTour->duration);
	printf("Visitor Amount: %u\n", pTour->visitorAmount);
	//TODO: tell guide event
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

int addRandomEvent(char* fileName, int length, CocaColaTour* pTour)
{
	// Set the upper bound for random numbers 
	int upper_bound = length-1;
	// Set the lower bound for random numbers 
	int lower_bound = 0;
	int index = rand() % (upper_bound - lower_bound + 1) + lower_bound;
	printf("index=%d\n", index);
	FILE* fp = fopen(fileName, "rb"); // Open in binary read mode
	if (!fp)
	{
		perror("Error opening file");
		return 1;
	}
	HistoricalEvent event;
	if (!getEventFromFileBySeek(fp,index,&event))
	{
		fclose(fp);
		return 0;
	}
	printHistoricalEvent(&event);
	fclose(fp);
	return 1;
}

int compareTourbyDuration(const void* t1, const void* t2)
{
	const CocaColaTour* pTour1 = (const CocaColaTour*)t1;
	const CocaColaTour* pTour2 = (const CocaColaTour*)t2;
	if (pTour1->duration > pTour2->duration)
		return 1;
	if (pTour1->duration < pTour2->duration)
		return -1;
	return 0;
}

int compareTourbyDateTime(const void* t1, const void* t2)
{
	const CocaColaTour* pTour1 = (const CocaColaTour*)t1;
	const CocaColaTour* pTour2 = (const CocaColaTour*)t2;
	return compareDateTime(&pTour1->dateTime, &pTour2->dateTime);
}
