#include "CocaColaFactoryFile.h"

int initFactoryFromBFile(CocaColaFactory* pFactory, const char* fileName, const char* eventsFileName)
{
	FILE* fp;
	fp = fopen(fileName, "rb");
	if (!fp)
	{
		printf("Error open Coca Cola Factory binary file to read\n");
		return 0;
	}

	if (!readIntFromFile(&pFactory->seed, fp, "Error reading employees count\n"))
	{
		fclose(fp);
		return 0;
	}
	srand(pFactory->seed);

	//-----------------------init all Employees------------------------------------
	pFactory->employees = NULL;
	if (!readIntFromFile(&pFactory->employeesCount, fp, "Error reading employees count\n"))
	{
		fclose(fp);
		return 0;
	}
	if(!createEmployeesArr(pFactory))
	{
		fclose(fp);//TODO: freeArr
		return 0;
	}
	if (!readEmployeesArrFromBFile(pFactory, fp))
	{
		//TODO: free employees arr
		free(pFactory->employees);
		fclose(fp);
		return 0;
	}
	
	//-----------------------init all Suppliers-----------------------------------------
	pFactory->suppliers = NULL;
	if (!readIntFromFile(&pFactory->suppliersCount, fp, "Error reading suppliers count\n"))
	{
		fclose(fp);
		return 0;
	}
	if (!createSuppliersArr(pFactory))
	{
		//TODO: free employees arr
		fclose(fp);
		return 0;
	}
	if (!readSuppliersArrFromBFile(pFactory, fp))
	{
		//TODO: free employees arr
		free(pFactory->suppliers);
		fclose(fp);
		return 0;
	}

	//----------------------------init all Trucks--------------------------------
	pFactory->trucks = NULL;
	if (!readIntFromFile(&pFactory->trucksCount, fp, "Error reading truck count\n"))
	{
		fclose(fp);
		return 0;
	}
	if (!createTruckArr(pFactory))
	{
		//TODO: free employees arr
		generalArrayFunction(pFactory->suppliers, pFactory->suppliersCount, sizeof(Supplier), freeSupplierPtr);
		free(pFactory->suppliers);
		fclose(fp);
		return 0;
	}
	if (!readTruckArrFromBFile(pFactory, fp))
	{
		//TODO: free employees arr
		generalArrayFunction(pFactory->suppliers, pFactory->suppliersCount, sizeof(Supplier), freeSupplierPtr);
		free(pFactory->suppliers);
		free(pFactory->trucks);
		fclose(fp);
		return 0;
	}

	//-------------------------init all Events---------------------------------
	if (!readEventsListFromBFile(pFactory, eventsFileName))
	{
		//TODO: free employees arr
		generalArrayFunction(pFactory->suppliers, pFactory->suppliersCount, sizeof(Supplier), freeSupplierPtr);
		free(pFactory->suppliers);
		free(pFactory->trucks);
		L_free(&pFactory->allEvents, freeHistoricalEvent);
		return 0;
	}

	//-------------------------init all Tours---------------------------------
	pFactory->tours = NULL;
	if (!readIntFromFile(&pFactory->toursCount, fp, "Error reading tour count\n"))
	{
		fclose(fp);
		return 0;
	}
	if (!createToursArr(pFactory))
	{
		//TODO: free employees arr
		generalArrayFunction(pFactory->suppliers, pFactory->suppliersCount, sizeof(Supplier), freeSupplierPtr);
		free(pFactory->suppliers);
		free(pFactory->trucks);
		fclose(fp);
		return 0;
	}
	if (!readToursArrFromBFile(pFactory, fp, eventsFileName, &pFactory->allEvents))
	{
		//TODO: free employees arr
		generalArrayFunction(pFactory->suppliers, pFactory->suppliersCount, sizeof(Supplier), freeSupplierPtr);
		free(pFactory->suppliers);
		L_free(&pFactory->allEvents, freeHistoricalEvent); //TODO: check if working
		free(pFactory->trucks);
		free(pFactory->tours);
		fclose(fp);
		return 0;
	}
	
	pFactory->sortTour = -1;//not sorted
	
	fclose(fp);
	return 1;
}

int createEmployeesArr(CocaColaFactory* pFactory)
{
	if (pFactory->employeesCount > 0)
	{
		pFactory->employees = (Employee**)malloc(pFactory->employeesCount * sizeof(Employee*));
		if (!pFactory->employees)
		{
			printf("Alocation error\n");
			return 0;
		}
	}
	else
		pFactory->employees = NULL;

	//for (int i = 0; i < pFactory->employeesCount; i++)
	//{
	//	pFactory->employees[i] = (Employee*)calloc(1, sizeof(Employee));
	//	if (!pFactory->employees[i])
	//	{
	//		printf("Alocation error\n");
	//		return 0;
	//	}
	//}
	return 1;
}

int createSuppliersArr(CocaColaFactory* pFactory)
{
	if (pFactory->suppliersCount > 0)
	{
		pFactory->suppliers = (Supplier**)malloc(pFactory->suppliersCount * sizeof(Supplier*));
		if (!pFactory->suppliers)
		{
			printf("Alocation error\n");
			return 0;
		}
	}
	else
		pFactory->suppliers = NULL;

	for (int i = 0; i < pFactory->suppliersCount; i++)
	{
		pFactory->suppliers[i] = (Supplier*)calloc(1, sizeof(Supplier));
		if (!pFactory->suppliers[i])
		{
			printf("Alocation error\n");
			return 0;
		}
	}
	return 1;
}

int readSuppliersArrFromBFile(CocaColaFactory* pFactory, FILE* fp)
{
	for (int i = 0; i < pFactory->suppliersCount; i++)
	{
		if (!readSupplierFromBFile(fp, pFactory->suppliers[i]))
			return 0;
	}
	return 1;
}

int readEmployeesArrFromBFile(CocaColaFactory* pFactory, FILE* fp)
{
	int type;
	for (int i = 0; i < pFactory->employeesCount; i++)
	{
		if(!readIntFromFile(&type, fp, "Error reading Employee Type\n"))
			return 0;
		switch (type) {
		case eDriver:
			if (!readDriverFromBFile(fp, &pFactory->employees[i]))
				return 0;
			break;
		case eGuide:
			if (!readGuideFromBFile(fp, &pFactory->employees[i]))
				return 0;
			break;
		default:
			printf("Error type value");
			return 0;
		}
	}
	return 1;
}

int createTruckArr(CocaColaFactory* pFactory)
{
	pFactory->trucks = (Truck*)malloc(pFactory->trucksCount * sizeof(Truck));
	if (!pFactory->trucks)
	{
		printf("Allocation error\n");
		return 0;
	}
	return 1;
}

int readTruckArrFromBFile(CocaColaFactory* pFactory, FILE* fp)
{
	int supplierId, driverId;

	for (int i = 0; i < pFactory->trucksCount; i++)
	{
		if (!readTruckFromBFile(fp, &pFactory->trucks[i], &supplierId, &driverId))
			return 0;

		pFactory->trucks[i].destSupplier = findSupplierById(pFactory->suppliers, pFactory->suppliersCount, supplierId);
		pFactory->trucks[i].driver = findEmployeeById(pFactory->employees, pFactory->employeesCount, driverId, eDriver);
	}
	return 1;
}

int createToursArr(CocaColaFactory* pFactory)
{
	if (pFactory->toursCount > 0)
	{
		pFactory->tours = (CocaColaTour**)malloc(pFactory->toursCount * sizeof(CocaColaTour*));
		if (!pFactory->tours)
		{
			printf("Alocation error\n");
			return 0;
		}
	}
	else
		pFactory->tours = NULL;

	for (int i = 0; i < pFactory->toursCount; i++)
	{
		pFactory->tours[i] = (CocaColaTour*)calloc(1, sizeof(CocaColaTour));
		if (!pFactory->tours[i])
		{
			printf("Alocation error\n");
			return 0;
		}
	}
	return 1;
}

int readToursArrFromBFile(CocaColaFactory* pFactory, FILE* fp, const char* eventsFileName, LIST* allEvents)
{
	int guideId;
	for (int i = 0; i < pFactory->toursCount; i++)
	{
		if (!readTourFromBFile(fp, pFactory->tours[i], &guideId, eventsFileName, allEvents))
			return 0;
		
		pFactory->tours[i]->guide = findEmployeeById(pFactory->employees, pFactory->employeesCount, guideId, eGuide);
	}
	return 1;
}

int saveFactoryToBFile(CocaColaFactory* pFactory, const char* fileName, const char* eventsFileName)
{
	FILE* fp;
	fp = fopen(fileName, "wb");
	if (!fp) {
		printf("Error open Coca Cola Factory binary file to write\n");
		return 0;
	}

	if (!writeIntToFile(pFactory->seed, fp, "Error write seed\n"))
	{
		fclose(fp);
		return 0;
	}

	//-------------------------write all Employees---------------------------------
	if (!writeIntToFile(pFactory->employeesCount, fp, "Error write employees count\n"))
	{
		fclose(fp);
		return 0;
	}
	for (int i = 0; i < pFactory->employeesCount; i++)
	{
		if (!pFactory->employees[i]->writeBFile(fp, pFactory->employees[i]))
		{
			fclose(fp);
			return 0;
		}
	}

	//-------------------------write all Suppliers---------------------------------
	if (!writeIntToFile(pFactory->suppliersCount, fp, "Error write suppliers count\n"))
	{
		fclose(fp);
		return 0;
	}
	for (int i = 0; i < pFactory->suppliersCount; i++)
	{
		if (!writeSupplierToBFile(fp, pFactory->suppliers[i]))
		{
			fclose(fp);
			return 0;
		}
	}

	//-------------------------write all Trucks---------------------------------
	if (!writeIntToFile(pFactory->trucksCount, fp, "Error write trucks count\n"))
	{
		fclose(fp);
		return 0;
	}
	for (int i = 0; i < pFactory->trucksCount; i++)
	{
		if (!writeTruckToBFile(fp, &pFactory->trucks[i]))
		{
			fclose(fp);
			return 0;
		}
	}

	//-------------------------write all Events---------------------------------
	if (!writeEventsListToBFile(pFactory, eventsFileName))
		return 0;

	//-------------------------write all Tours---------------------------------
	if (!writeIntToFile(pFactory->toursCount, fp, "Error write tours count\n"))
	{
		fclose(fp);
		return 0;
	}
	for (int i = 0; i < pFactory->toursCount; i++)
	{
		if (!writeTourToBFile(fp, pFactory->tours[i]))
		{
			fclose(fp);
			return 0;
		}
	}

	fclose(fp);
	return 1;
}

int writeEventsListToBFile(CocaColaFactory* pFactory, const char* eventsFileName)
{
	FILE* fp;
	fp = fopen(eventsFileName, "wb");
	if (!fp) {
		printf("Error open historical events binary file.\n");
		return 0;
	}
	int size = L_length(&pFactory->allEvents);
	if (!writeIntToFile(size, fp, "Error writing Events amount"))
	{
		fclose(fp);
		return 0;
	}
	NODE* pNode = pFactory->allEvents.head.next;
	while (pNode)
	{
		if (!writeEventToBFile(fp, pNode->key))
		{
			fclose(fp);
			return 0;
		}
		pNode = pNode->next;
	}
	fclose(fp);
	return 1;
}

int writeEventsListToTxtFile(CocaColaFactory* pFactory, const char* eventsFileName)
{
	FILE* fp;
	fp = fopen(eventsFileName, "w");
	if (!fp) {
		printf("Error open historical events text file.\n");
		return 0;
	}
	int size = L_length(&pFactory->allEvents);
	fprintf(fp, "%d\n", size);
	NODE* pNode = pFactory->allEvents.head.next;
	while (pNode)
	{
		if (!writeEventToTxtFile(fp, pNode->key))
		{
			fclose(fp);
			return 0;
		}
		pNode = pNode->next;
	}
	fclose(fp);
	return 1;
}

int readEventsListFromTxtFile(CocaColaFactory* pFactory, const char* eventsFileName)
{
	FILE* fp;

	fp = fopen(eventsFileName, "r");
	if (!fp)
	{
		printf("Error open historical events text file\n");
		return 0;
	}

	L_init(&pFactory->allEvents);
	int count;
	fscanf(fp, "%d", &count);
	//clean the buffer
	fgetc(fp);

	HistoricalEvent* pEvent;
	for (int i = 0; i < count; i++)
	{
		pEvent = (HistoricalEvent*)malloc(sizeof(HistoricalEvent));
		if (!pEvent)
			break;
		if (!readEventFromTxtFile(fp, pEvent))
		{
			printf("Error read event from file\n");
			fclose(fp);
			return 0;
		}
		NODE* pNode;
		pNode = L_insert_sorted(&pFactory->allEvents, pEvent, compareEventByDateTime);//add event by dateTime
		if (!pNode)
		{
			fclose(fp);
			return 0;
		}
	}
	fclose(fp);
	return 1;
}

int readEventsListFromBFile(CocaColaFactory* pFactory, const char* eventsFileName)
{
	FILE* fp;

	fp = fopen(eventsFileName, "rb");
	if (!fp)
	{
		printf("Error open historical events binary file\n");
		return 0;
	}

	L_init(&pFactory->allEvents);
	int count;
	if (!readIntFromFile(&count, fp, "Error reading events amount.\n"))
	{
		fclose(fp);
		return 0;
	}
	HistoricalEvent* pEvent;
	for (int i = 0; i < count; i++)
	{
		pEvent = (HistoricalEvent*)malloc(sizeof(HistoricalEvent));
		if (!pEvent)
			break;
		if (!readEventFromBFile(fp, pEvent))
		{
			printf("Error read event from file\n");
			fclose(fp);
			return 0;
		}
		NODE* pNode;
		pNode = L_insert_sorted(&pFactory->allEvents, pEvent, compareEventByDateTime);//add event by dateTime
		if (!pNode)
		{
			fclose(fp);
			return 0;
		}
	}
	fclose(fp);
	return 1;
}

int initFactoryFromTxtFile(CocaColaFactory* pFactory, const char* fileName, const char* eventsFileName)
{
	FILE* fp;
	fp = fopen(fileName, "r");
	if (!fp) {
		printf("Error open Coca Cola Factory text file to read\n");
		return 0;
	}

	if (fscanf(fp, "%d", &pFactory->seed) != 1)
	{
		fclose(fp);
		return 0;
	}
	srand(pFactory->seed);

	//-----------------------init all Employees------------------------------------
	pFactory->employees = NULL;
	if (fscanf(fp, "%d", &pFactory->employeesCount) != 1)
	{
		fclose(fp);
		return 0;
	}
	if (!createEmployeesArr(pFactory))
	{
		fclose(fp);
		return 0;
	}
	if (!readEmployeesArrFromTxtFile(pFactory, fp)) // TODO: check
	{
		//TODO: free employees arr
		free(pFactory->employees);
		fclose(fp);
		return 0;
	}

	//-----------------------init all Suppliers-----------------------------------------
	pFactory->suppliers = NULL;
	if (fscanf(fp, "%d", &pFactory->suppliersCount) != 1)
	{
		fclose(fp);
		return 0;
	}
	if (!createSuppliersArr(pFactory))
	{
		//TODO: free employees arr
		fclose(fp);
		return 0;
	}
	if (!readSuppliersArrFromBFile(pFactory, fp))
	{
		//TODO: free employees arr
		free(pFactory->suppliers);
		fclose(fp);
		return 0;
	}

	//----------------------------init all Trucks--------------------------------
	pFactory->trucks = NULL;
	if (fscanf(fp, "%d", &pFactory->trucksCount) != 1)
	{
		fclose(fp);
		return 0;
	}
	if (!createTruckArr(pFactory))
	{
		//TODO: free employees arr
		generalArrayFunction(pFactory->suppliers, pFactory->suppliersCount, sizeof(Supplier), freeSupplierPtr);
		free(pFactory->suppliers);
		fclose(fp);
		return 0;
	}
	if (!readTruckArrFromTxtFile(pFactory, fp))
	{
		//TODO: free employees arr
		generalArrayFunction(pFactory->suppliers, pFactory->suppliersCount, sizeof(Supplier), freeSupplierPtr);
		free(pFactory->suppliers);
		free(pFactory->trucks);
		fclose(fp);
		return 0;
	}

	//-------------------------init all Events---------------------------------
	if (!readEventsListFromTxtFile(pFactory, eventsFileName))
	{
		//TODO: free employees arr
		generalArrayFunction(pFactory->suppliers, pFactory->suppliersCount, sizeof(Supplier), freeSupplierPtr);
		free(pFactory->suppliers);
		L_free(&pFactory->allEvents, freeHistoricalEvent);
		return 0;
	}

	//-------------------------init all Tours---------------------------------
	pFactory->tours = NULL;
	if (fscanf(fp, "%d", &pFactory->toursCount) != 1)
	{
		fclose(fp);
		return 0;
	}
	if (!createToursArr(pFactory))
	{
		//TODO: free employees arr
		generalArrayFunction(pFactory->suppliers, pFactory->suppliersCount, sizeof(Supplier), freeSupplierPtr);
		free(pFactory->suppliers);
		L_free(&pFactory->allEvents, freeHistoricalEvent); //TODO: check if working
		free(pFactory->trucks);
		fclose(fp);
		return 0;
	}
	if (!readToursArrFromTxtFile(pFactory, fp))
	{
		//TODO: free employees arr
		generalArrayFunction(pFactory->suppliers, pFactory->suppliersCount, sizeof(Supplier), freeSupplierPtr);
		free(pFactory->suppliers);
		L_free(&pFactory->allEvents, freeHistoricalEvent); //TODO: check if working
		free(pFactory->trucks);
		free(pFactory->tours);
		fclose(fp);
		return 0;
	}

	pFactory->sortTour = -1;//not sorted

	fclose(fp);
	return 1;
}

int readEmployeesArrFromTxtFile(CocaColaFactory* pFactory, FILE* fp)
{
	int type;
	for (int i = 0; i < pFactory->employeesCount; i++)
	{
		if (fscanf(fp, "%d", &type) != 1)
			return 0;
		switch (type) {
		case eDriver:
			if (!readDriverFromTxtFile(fp, &pFactory->employees[i]))
				return 0;
			break;
		case eGuide:
			if (!readGuideFromTxtFile(fp, &pFactory->employees[i]))
				return 0;
			break;
		default:
			printf("Error type value");
			return 0;
		}
	}
	return 1;
}

int readSuppliersArrFromTxtFile(CocaColaFactory* pFactory, FILE* fp)
{
	for (int i = 0; i < pFactory->suppliersCount; i++)
	{
		if (!readSupplierFromTxtFile(fp, pFactory->suppliers[i]))
			return 0;
	}
	return 1;
}

int readTruckArrFromTxtFile(CocaColaFactory* pFactory, FILE* fp)
{
	int supplierId, driverId;

	for (int i = 0; i < pFactory->trucksCount; i++)
	{
		if (!readTruckFromTxtFile(fp, &pFactory->trucks[i], &supplierId, &driverId))
			return 0;

		pFactory->trucks[i].destSupplier = findSupplierById(pFactory->suppliers, pFactory->suppliersCount, supplierId);
		pFactory->trucks[i].driver = findEmployeeById(pFactory->employees, pFactory->employeesCount, driverId, eDriver);
	}
	return 1;
}

int readToursArrFromTxtFile(CocaColaFactory* pFactory, FILE* fp)
{
	int guideId;
	for (int i = 0; i < pFactory->toursCount; i++)
	{
		if (!readTourFromTxtFile(fp, pFactory->tours[i], &guideId))
			return 0;

		pFactory->tours[i]->guide = findEmployeeById(pFactory->employees, pFactory->employeesCount, guideId, eGuide);
	}
	return 1;
}

int saveFactoryToTxtFile(CocaColaFactory* pFactory, const char* fileName, const char* eventsFileName)
{
	FILE* fp;
	fp = fopen(fileName, "w");
	if (!fp) {
		printf("Error open Coca Cola Factory text file to write\n");
		return 0;
	}

	fprintf(fp, "%d\n", pFactory->seed);

	//-------------------------write all Employees---------------------------------
	fprintf(fp, "%d\n", pFactory->employeesCount);
	for (int i = 0; i < pFactory->employeesCount; i++)
	{
		if (!pFactory->employees[i]->writeTFile(fp, pFactory->employees[i]))
		{
			fclose(fp);
			return 0;
		}
	}

	//-------------------------write all Suppliers---------------------------------
	fprintf(fp, "%d\n", pFactory->suppliersCount);
	for (int i = 0; i < pFactory->suppliersCount; i++)
	{
		if (!writeSupplierToTxtFile(fp, pFactory->suppliers[i]))
		{
			fclose(fp);
			return 0;
		}
	}

	//-------------------------write all Trucks---------------------------------
	fprintf(fp, "%d\n", pFactory->trucksCount);
	for (int i = 0; i < pFactory->trucksCount; i++)
	{
		if (!writeTruckToTxtFile(fp, &pFactory->trucks[i]))
		{
			fclose(fp);
			return 0;
		}
	}


	//-------------------------write all Events---------------------------------
	if (!writeEventsListToTxtFile(pFactory, eventsFileName))
		return 0;

	//-------------------------write all Tours---------------------------------
	fprintf(fp, "%d\n", pFactory->toursCount);
	for (int i = 0; i < pFactory->toursCount; i++)
	{
		if (!writeTourToTxtFile(fp, pFactory->tours[i]))
		{
			fclose(fp);
			return 0;
		}
	}

	fclose(fp);
	return 1;
}
