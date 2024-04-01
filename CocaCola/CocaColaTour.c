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

void freeCocaColaTour(const CocaColaTour* pTour)
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
