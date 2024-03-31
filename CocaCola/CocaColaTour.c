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
