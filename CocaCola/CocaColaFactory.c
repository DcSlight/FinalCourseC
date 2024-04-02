#include "CocaColaFactory.h"

static const char* TourStr[eNofTourTypes]
= { "Employee Guide", "Duration", "DateTime" };

int initFactory(CocaColaFactory* pFactory)
{
	if (!L_init(&pFactory->allEvents))
		return 0;
	pFactory->employees = NULL;
	pFactory->employeesCount = 0;
	pFactory->trucks = NULL;
	pFactory->trucksCount = 0;
	pFactory->suppliers = NULL;
	pFactory->suppliersCount = 0;
	pFactory->tours = NULL;
	pFactory->toursCount = 0;	
	return 1;
}

int addEventToFactory(CocaColaFactory* pFactory)
{
	HistoricalEvent* event = (HistoricalEvent*)malloc(sizeof(HistoricalEvent));
	if (!event)
		return 0;
	initHistoricalEvent(event);
	const NODE* pNode = L_find(pFactory->allEvents.head.next, event, compareEventByDescription);
	if (pNode)//ensure that we don't have duplication
		return 0;
	pNode = L_insert_sorted(&pFactory->allEvents, event, compareEventByDateTime);//add event by dateTime
	if (!pNode)
		return 0;
	return 1;
}

int addSupplier(CocaColaFactory* pFactory)
{
	Supplier* pSupplier = (Supplier*)malloc(sizeof(Supplier));
	if (!pSupplier)
		return 0;
	initSupplier(pSupplier);
	pFactory->suppliers = (Supplier**)realloc(pFactory->suppliers, (pFactory->suppliersCount + 1) * sizeof(Supplier*));
	if (!pFactory->suppliers)
	{
		free(pSupplier);
		return 0;
	}
	pFactory->suppliers[pFactory->suppliersCount] = pSupplier;
	pFactory->suppliersCount++;
	return 1;
}

int addTruck(CocaColaFactory* pFactory)
{
	pFactory->trucks = (Truck*)realloc(pFactory->trucks, (pFactory->trucksCount + 1) * sizeof(Truck));
	if (!pFactory->trucks)
		return 0;
	Truck t;
	initTruck(&t);
	pFactory->trucks[pFactory->trucksCount] = t;
	pFactory->trucksCount++;
	return 1;
}

void printTrucksArr(CocaColaFactory* pFactory)
{
	printf("There are %d trucks\n", pFactory->trucksCount);
	for (int i = 0; i < pFactory->trucksCount; i++)
	{
		printTruck(&pFactory->trucks[i]);
		printf("\n");
	}
}

void printSuppliersArr(CocaColaFactory* pFactory)
{
	printf("The are %d suppliers\n", pFactory->suppliersCount);
	for (int i = 0; i < pFactory->suppliersCount; i++)
	{
		printSupplier(pFactory->suppliers[i]);
		printf("\n");
	}
}

int addTour(CocaColaFactory* pFactory)
{
	/*CocaColaTour* pTour = (CocaColaTour*)malloc(sizeof(CocaColaTour));
	if (!pTour)
		return 0;
	#ifdef B_FILE
	initCocaColaTour(pTour, FACTORY_B_FILE);
	#elif defined(T_FILE)
	initCocaColaTour(pTour, FACTORY_T_FILE);
	#else
	initCocaColaTour(pTour, NULL);
	#endif	*/
	return 1;
}

