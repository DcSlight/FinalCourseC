#ifndef __COCA_COLA_FACTORY__
#define __COCA_COLA_FACTORY__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Employee.h"
#include "GuideEmployee.h"
#include "DriverEmployee.h"
#include "Truck.h"
#include "CocaColaTour.h"
#include "Supplier.h"
#include "List.h"

typedef enum {
	eEmployeeGuide, eDuration, eDateTime, eNofTourTypes
} eTourSort;

static const char* TourStr[eNofTourTypes];


#define ERROR 0
#define FROM_B_FILE 1
#define FROM_T_FILE 2
#define FROM_USER 3

#define FACTORY_B_FILE "CocaColaFactory.bin"
#define FACTORY_T_FILE "CocaColaFactory.txt"

#define FACTORY_EVENTS_FILE_B "CocaColaEvents.bin"

typedef struct
{
	Employee** employees;
	int employeesCount;
	Truck* trucks;
	int trucksCount;
	Supplier** suppliers;
	int suppliersCount;
	CocaColaTour** tours;
	int toursCount;
	LIST allEvents;
	eTourSort sortTour;
	unsigned seed;
}CocaColaFactory;

int initFactory(CocaColaFactory* pFactory);
int addEmployee(CocaColaFactory* pFactory);
int addEventToFactory(CocaColaFactory* pFactory);
int addSupplier(CocaColaFactory* pFactory);
int addTruck(CocaColaFactory* pFactory);
Supplier* getSupplier(CocaColaFactory* pFactory);
Supplier* findSupplierById(Supplier** allSuppliers, int supplierCount, int id);
int countEmployeesByType(Employee** allEmployees, int employeeCount, eEmployeeType type);
Employee* getEmployee(CocaColaFactory* pFactory, eEmployeeType type);
Employee* findEmployeeById(Employee** allEmployees, int employeeCount, int id, eEmployeeType type);
void printFactory(const CocaColaFactory* pFactory);
void printTrucksArr(const Truck* trucksArr,int trucksCount);//TODO: print void*
void printSuppliersArr(const Supplier** suppliersArr, int suppliersCount);//TODO: print void*
void printEmployeesArr( Employee** const employeesArr, int employeesCount); //TODO :print void*

int addTour(CocaColaFactory* pFactory);
void EnterTour(const CocaColaFactory* pFactory);
void printTours(const CocaColaTour** toursArr, int toursCount);
eTourSort showSortMenu();
void sortTours(CocaColaFactory* pFactory);
void findTour(const CocaColaFactory* pFactory);


#endif /* __COCA_COLA_FACTORY__ */
