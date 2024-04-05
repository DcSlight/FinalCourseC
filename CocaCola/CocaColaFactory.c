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
	pFactory->seed = (unsigned)time(NULL);
	srand(pFactory->seed);
	return 1;
}

int addEmployee(CocaColaFactory* pFactory)
{
	eEmployeeType employeeType= getEmployeeType();
	pFactory->employees = (Employee**)realloc(pFactory->employees, (pFactory->employeesCount + 1) * sizeof(Employee*));
	if (employeeType == eDriver)
	{// Driver
		initEmployeeDriver(&pFactory->employees[pFactory->employeesCount]);
	}
	else
	{// Guide
		initEmployeeGuide(&pFactory->employees[pFactory->employeesCount]);
	}
	pFactory->employeesCount++;
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
	{
		printf("Event already exist in factory\n");
		return 0;
	}
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
	initSupplier(pSupplier,pFactory->suppliers,pFactory->suppliersCount);
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
	if (pFactory->suppliersCount == 0)
	{
		printf("There is no suppliers in company\n");
		return 0;
	}
	if (countEmployeesByType(pFactory->employees, pFactory->employeesCount, eDriver) == 0)
	{
		printf("There is no driver employees in company\n");
		return 0;
	}
	printf("\nAdd a truck\n");
	Supplier* pSupplier = getSupplier(pFactory);
	Employee* pEmployee = getEmployee(pFactory, eDriver);
	pFactory->trucks = (Truck*)realloc(pFactory->trucks, (pFactory->trucksCount + 1) * sizeof(Truck));
	if (!pFactory->trucks)
		return 0;
	Truck t;
	initTruck(&t, pSupplier, pEmployee);
	pFactory->trucks[pFactory->trucksCount] = t;
	pFactory->trucksCount++;
	return 1;
}

Supplier* getSupplier(CocaColaFactory* pFactory)
{
	Supplier* pSupplier;
	int id;
	printf("--------------------------------------------\n");
	printSuppliersArr(pFactory->suppliers,pFactory->suppliersCount);
	printf("\nChoose a supplier from list, type its id\n");
	do {
		scanf("%d", &id);
		pSupplier = findSupplierById(pFactory->suppliers, pFactory->suppliersCount, id);
		if (!pSupplier)
			printf("No supplier with that id! Try again!\n");
	} while (pSupplier == NULL);

	return pSupplier;
}

Supplier* findSupplierById(Supplier** allSuppliers, int supplierCount, int id)
{
	for (int i = 0; i < supplierCount; i++)
	{
		if (allSuppliers[i]->id == id)
			return allSuppliers[i];
	}
	return NULL;
}

int countEmployeesByType(Employee** allEmployees, int employeeCount, eEmployeeType type)
{
	int counter = 0;
	for (int i = 0; i < employeeCount; i++)
	{
		if (allEmployees[i]->type == type)
			counter++;
	}
	return counter;
}

Employee* getEmployee(CocaColaFactory* pFactory, eEmployeeType type)
{
	Employee* pEmployee;
	int id;
	printf("\n--------------------------------------------\n");
	printEmployeesArr(pFactory->employees,pFactory->employeesCount);//TODO: print void* generalFunc
	printf("Choose a %s employee from list, type its id\n", EmployeeStr[type]);
	do {
		scanf("%d", &id);
		pEmployee = findEmployeeById(pFactory->employees, pFactory->employeesCount, id, type);
		if (!pEmployee)
			printf("No %s employee with that id! Try again!\n", EmployeeStr[type]);
	} while (pEmployee == NULL);

	return pEmployee;
}

Employee* findEmployeeById(Employee** allEmployees, int employeeCount, int id, eEmployeeType type)
{
	for (int i = 0; i < employeeCount; i++)
	{
		if (allEmployees[i]->type == type)
			if (allEmployees[i]->id == id)
				return allEmployees[i];
	}
	return NULL;
}

void printFactory(const CocaColaFactory* pFactory)
{//print factory will not print the listEvents - have a seperated function
	printf(ANSI_COLOR_CYAN"\n---------------------------------------------------\n"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_CYAN "\t\tCoca Cola Factory\n" ANSI_COLOR_RESET);
	printf(ANSI_COLOR_CYAN"---------------------------------------------------\n"ANSI_COLOR_RESET);
	printEmployeesArr(pFactory->employees, pFactory->employeesCount);
	printSuppliersArr(pFactory->suppliers, pFactory->suppliersCount);
	printTrucksArr(pFactory->trucks, pFactory->trucksCount);
	printTours(pFactory->tours, pFactory->toursCount);
}

void printTrucksArr(const Truck* trucksArr, int trucksCount)
{
	printf("There are %d trucks\n", trucksCount);
	for (int i = 0; i < trucksCount; i++)
	{
		printTruck(&trucksArr[i]);
		printf("\n");
	}
}

void printSuppliersArr(const Supplier** suppliersArr, int suppliersCount)
{
	printf("The are %d suppliers\n", suppliersCount);
	for (int i = 0; i < suppliersCount; i++)
	{
		printSupplier(suppliersArr[i]);
		printf("\n");
	}
}

void printEmployeesArr( Employee** const employeesArr, int employeesCount)
{
	for (int i = 0; i < employeesCount; i++)
	{
		employeesArr[i]->print(employeesArr[i]);
	}
}

int addTour(CocaColaFactory* pFactory)
{
	Employee* pGuide;
	if (countEmployeesByType(pFactory->employees, pFactory->employeesCount, eGuide) == 0)
	{
		printf("There is no guide employees in company\n");
		return 0;
	}
	pGuide = getEmployee(pFactory, eGuide);
	CocaColaTour* pTour = (CocaColaTour*)malloc(sizeof(CocaColaTour));
	if (!pTour)
		return 0;
	if (!initCocaColaTour(pTour, pGuide, NULL, &pFactory->allEvents))
		return 0;
	pFactory->tours = (CocaColaTour**)realloc(pFactory->tours,(pFactory->toursCount + 1) * sizeof(CocaColaTour*));
	if (!pFactory->tours)
		return 0;
	pFactory->tours[pFactory->toursCount] = pTour;
	pFactory->toursCount++;
	return 1;
}

void EnterTour(const CocaColaFactory* pFactory)
{
	int index;
	printf("There are %d tours\n", pFactory->toursCount);
	do
	{
		printf("Pick a tour to start\n");
		scanf("%d", &index);
	} while (index <= 0 || index > pFactory->toursCount);
	startTour(pFactory->tours[index - 1]);
}

void printTours(const CocaColaTour** toursArr, int toursCount)
{
	for (int i = 0; i < toursCount; i++)
	{
		printCocaColaTour(toursArr[i]);
	}
}

eTourSort showSortMenu()
{
	int opt;
	printf("Base on what field do you want to sort your tours?\n");
	do {
		for (int i = 1; i < eNofTourTypes; i++)
			printf("Enter %d for %s\n", i, TourStr[i]);
		scanf("%d", &opt);
	} while (opt < 0 || opt >= eNofTourTypes);

	return (eTourSort)opt;
}

void sortTours(CocaColaFactory* pFactory)
{
	pFactory->sortTour = showSortMenu();
	int(*compare)(const void* tour1, const void* tour2) = NULL;

	switch (pFactory->sortTour)
	{
	case eEmployeeGuide:
		compare = compareTourByGuide;
		break;
	case eDuration:
		compare = compareTourByDuration;
		break;
	case eDateTime:
		compare = compareTourByDateTime;
		break;
	}

	if (compare != NULL)
		qsort(pFactory->tours, pFactory->toursCount, sizeof(CocaColaTour*), compare);
}

void findTour(const CocaColaFactory* pFactory)
{
	int(*compare)(const void* tour1, const void* tour2) = NULL;
	CocaColaTour tour = { 0 };
	CocaColaTour* pTour = &tour;
	int id;
	switch (pFactory->sortTour)
	{
	case eEmployeeGuide:
		printf("Enter guide id:\t");
		scanf("%d", &id);
		pTour->guide=newEmployeeGuide(NULL, id, 0, eGuide, 0, 0);
		compare = compareTourByGuide;
		break;

	case eDuration:
		printf("Enter duration:\t");
		scanf("%u", &pTour->duration);
		compare = compareTourByDuration;
		break;

	case eDateTime:
		initDateTime(&pTour->dateTime, 0);
		compare = compareTourByDateTime;
		break;
	}

	if (compare != NULL)
	{
		CocaColaTour** pToursArr = bsearch(&pTour, pFactory->tours, pFactory->toursCount, sizeof(CocaColaTour*), compare);
		if (pToursArr == NULL)
			printf("Coca Cola Tour was not found\n");
		else {
			printf("Coca Cola Tour found:\n");
			printCocaColaTour(pTour);
		}
	}
	else {
		printf("The search cannot be performed, array not sorted\n");
	}
}

