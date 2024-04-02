#ifndef __TRUCK__
#define __TRUCK__

#include <stdio.h>
#include <ctype.h>
#include "Supplier.h"
#include "Employee.h"
#include "DriverEmployee.h"
#include "BottlePacking.h"
#include "General.h"

#define MAX_PACKS 10
#define LICENSE_LEN 7

typedef struct
{
	Supplier* destSupplier;
	BottlePacking packs[MAX_PACKS];
	char truckLicenseCode[LICENSE_LEN];
	Employee* driver;
	int packAmount;
} Truck;

int initTruck(Truck* pTruck, Employee** employees, int employeesCount, Supplier** suppliers, int suppliersCount);
int getSupplier(Truck* pTruck, Supplier** suppliers, int suppliersCount);
void getLicenseCode(char* code);
int addPack(Truck* pTruck);
void printTruck(const Truck* pTruck);
void printTruckContent(const Truck* pTruck);
void freeTruck(Truck* pTruck);

#endif /* __TRUCK__ */