#include "CocaColaFactoryFile.h"

int initFactoryFromBFile(CocaColaFactory* pFactory, const char* fileName)
{
	FILE* fp;
	fp = fopen(fileName, "rb");
	if (!fp)
	{
		printf("Error open Coca Cola Factory binary file to read\n");
		return 0;
	}

	//TODO: read seed

	//-----------------------init all Employees------------------------------------
	pFactory->employees = NULL;
	if (!readIntFromFile(&pFactory->employeesCount, fp, "Error reading employees count\n"))
	{
		fclose(fp);
		return 0;
	}
	//TODO: create employees arr (allocating memory)
	//TODO: read employees arr from b file
	
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
		//TODO: free suppliers arr
		fclose(fp);
		return 0;
	}
	if (!readTruckArrFromBFile(pFactory, fp))
	{
		//TODO: free employees arr
		//TODO: free suppliers arr
		free(pFactory->trucks);
		fclose(fp);
		return 0;
	}

	//-------------------------init all Events---------------------------------
	int eventsCount = 0;
	if (!readIntFromFile(&eventsCount, fp, "Error reading events count\n"))
	{
		fclose(fp);
		return 0;
	}
	//TODO: read all historical events arr from b file

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
		//TODO: free suppliers arr
		//TODO: free events arr
		//TODO: free tours arr - (free all tours and tours array)
		fclose(fp);
		return 0;
	}
	if (!readToursArrFromBFile(pFactory, fp))
	{
		//TODO: free employees arr
		//TODO: free suppliers arr
		L_free(&pFactory->allEvents, freeHistoricalEvent); //TODO: check if working
		//TODO: free tours arr - (free all tours and tours array)
		free(pFactory->trucks);
		fclose(fp);
		return 0;
	}
	
	
	//TODO: eSort = eNone
	
	fclose(fp);
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

int createTruckArr(CocaColaFactory* pFactory)
{
	pFactory->trucks = (Truck*)malloc(pFactory->trucksCount * sizeof(Truck));
	if (!pFactory->trucks)
	{
		printf("Alocation error\n");
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

int readToursArrFromBFile(CocaColaFactory* pFactory, FILE* fp)
{
	int guideId;
	for (int i = 0; i < pFactory->toursCount; i++)
	{
		if (!readTourFromBFile(fp, pFactory->tours[i], &guideId))
			return 0;
		
		pFactory->tours[i]->guide = findEmployeeById(pFactory->employees, pFactory->employeesCount, guideId, eGuide);
	}
	return 1;
}

int saveFactoryToBFile(CocaColaFactory* pFactory, const char* fileName)
{
	FILE* fp;
	fp = fopen(fileName, "wb");
	if (!fp) {
		printf("Error open Coca Cola Factory binary file to write\n");
		return 0;
	}

	//TODO: write seed

	//-------------------------write all Employees---------------------------------
	if (!writeIntToFile(pFactory->employeesCount, fp, "Error write employees count\n"))
	{
		fclose(fp);
		return 0;
	}
	for (int i = 0; i < pFactory->employeesCount; i++)
	{
		//TODO: write employee to b file
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
	//TODO: write all historical events arr to b file


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

int initFactoryFromTxtFile(CocaColaFactory* pFactory, const char* fileName)
{
	FILE* fp;
	fp = fopen(fileName, "r");
	if (!fp) {
		printf("Error open Coca Cola Factory text file to read\n");
		return 0;
	}

	//TODO: read seed

	//-----------------------init all Employees------------------------------------

	//-----------------------init all Suppliers-----------------------------------------

	//----------------------------init all Trucks--------------------------------

	//-------------------------init all Events---------------------------------

	//-------------------------init all Tours---------------------------------


	fclose(fp);
	return 1;
}

int saveFactoryFromTxtFile(CocaColaFactory* pFactory, const char* fileName)
{
	FILE* fp;
	fp = fopen(fileName, "w");
	if (!fp) {
		printf("Error open Coca Cola Factory text file to write\n");
		return 0;
	}

	//TODO: write seed

	//-------------------------write all Employees---------------------------------
	//TODO: write employees to text file

	//-------------------------write all Suppliers---------------------------------
	fprintf(fp, "%d\n", pFactory->suppliersCount);
	for (int i = 0; i < pFactory->suppliersCount; i++)
	{
		if (writeSupplierToTxtFile(fp, pFactory->suppliers[i]))
		{
			fclose(fp);
			return 0;
		}
	}

	//-------------------------write all Trucks---------------------------------
	fprintf(fp, "%d\n", pFactory->trucksCount);
	for (int i = 0; i < pFactory->trucksCount; i++)
	{
		if (writeTruckToTxtFile(fp, &pFactory->trucks[i]))
		{
			fclose(fp);
			return 0;
		}
	}


	//-------------------------write all Events---------------------------------
	//TODO: write all historical events arr to text file

	//-------------------------write all Tours---------------------------------
	fprintf(fp, "%d\n", pFactory->toursCount);
	for (int i = 0; i < pFactory->toursCount; i++)
	{
		if (writeTourToTxtFile(fp, pFactory->tours[i]))
		{
			fclose(fp);
			return 0;
		}
	}

	fclose(fp);
	return 1;
}
