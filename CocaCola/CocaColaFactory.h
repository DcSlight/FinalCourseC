#ifndef __COCA_COLA_FACTORY__
#define __COCA_COLA_FACTORY__

#include <stdio.h>
#include <stdlib.h>
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
}CocaColaFactory;

int initFactory(CocaColaFactory* pFactory);
int addEventToFactory(CocaColaFactory* pFactory);

#endif
