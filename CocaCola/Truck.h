#ifndef __TRUCK__
#define __TRUCK__

#include <stdio.h>
#include <ctype.h>
#include "Supplier.h"
#include "Employee.h"
#include "CocaColaFunctions.h"
#include "DriverEmployee.h"
#include "BottlePacking.h"
#include "General.h"

#define MAX_PACKS 10
#define LICENSE_LEN 7

typedef struct
{
	Supplier* destSupplier;
	BottlePacking packs[MAX_PACKS];
	char truckLicenseCode[LICENSE_LEN+1];
	Employee* driver;
	int packAmount;
} Truck;

int initTruck(Truck* pTruck, Supplier* theSupplier, Employee* theDriver);
void getLicenseCode(char* code);
int addPack(Truck* pTruck);
void printTruck(const Truck* pTruck);
void printTruckContent(const Truck* pTruck);


int writeTruckToBFile(FILE* fp, const Truck* pTruck);
int readTruckFromBFile(FILE* fp, Truck* pTruck, int* supplierId, int* driverId);
int writeTruckToTxtFile(FILE* fp, const Truck* pTruck);
int readTruckFromTxtFile(FILE* fp, Truck* pTruck, int* supplierId, int* driverId);

#endif /* __TRUCK__ */