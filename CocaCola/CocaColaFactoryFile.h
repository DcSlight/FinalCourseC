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

int initFactoryFromBFile(CocaColaFactory* pFactory, const char* fileName);
int createSuppliersArr(CocaColaFactory* pFactory);
int readSuppliersArrFromBFile(CocaColaFactory* pFactory, FILE* fp);
int createTruckArr(CocaColaFactory* pFactory);
int readTruckArrFromBFile(CocaColaFactory* pFactory, FILE* fp);
int createToursArr(CocaColaFactory* pFactory);
int readToursArrFromBFile(CocaColaFactory* pFactory, FILE* fp);

int saveFactoryToBFile(CocaColaFactory* pFactory, const char* fileName);


#endif /* __COCA_COLA_FACTORY_FILE__ */
