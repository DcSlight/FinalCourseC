#ifndef __COCA_COLA_FACTORY_FILE__
#define __COCA_COLA_FACTORY_FILE__

#include <stdio.h>
#include <stdlib.h>
#include "CocaColaFactory.h"
#include "FileHelper.h"
#include "Truck.h"
#include "Employee.h"
#include "CocaColaTour.h"
#include "List.h"

int initFactoryFromBFile(CocaColaFactory* pFactory, const char* fileName, const char* eventsFileName);
int createEmployeesArr(CocaColaFactory* pFactory);
int createSuppliersArr(CocaColaFactory* pFactory);
int readEmployeesArrFromBFile(CocaColaFactory* pFactory, FILE* fp);
int readSuppliersArrFromBFile(CocaColaFactory* pFactory, FILE* fp);
int createTruckArr(CocaColaFactory* pFactory);
int readTruckArrFromBFile(CocaColaFactory* pFactory, FILE* fp);
int createToursArr(CocaColaFactory* pFactory);
int readToursArrFromBFile(CocaColaFactory* pFactory, FILE* fp, const char* eventsFileName, LIST* allEvents);
int saveFactoryToBFile(CocaColaFactory* pFactory, const char* fileName, const char* eventsFileName);
int writeEventsListToBFile(CocaColaFactory* pFactory, const char* eventsFileName);
int writeEventsListToTxtFile(CocaColaFactory* pFactory, const char* eventsFileName);
int readEventsListFromTxtFile(CocaColaFactory* pFactory, const char* eventsFileName);
int readEventsListFromBFile(CocaColaFactory* pFactory, const char* eventsFileName);

int initFactoryFromTxtFile(CocaColaFactory* pFactory, const char* fileName, const char* eventsFileName);
int readEmployeesArrFromTxtFile(CocaColaFactory* pFactory, FILE* fp);
int readSuppliersArrFromTxtFile(CocaColaFactory* pFactory, FILE* fp);
int readTruckArrFromTxtFile(CocaColaFactory* pFactory, FILE* fp);
int readToursArrFromTxtFile(CocaColaFactory* pFactory, FILE* fp);
int saveFactoryToTxtFile(CocaColaFactory* pFactory, const char* fileName, const char* eventsFileName);


#endif /* __COCA_COLA_FACTORY_FILE__ */
