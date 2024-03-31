#include <stdio.h>
#include "DateTime.h"
#include "Employee.h"
#include "GuideEmployee.h"
#include "DriverEmployee.h"
#include "Bottle.h"
#include "Address.h"
#include "Supplier.h"
#include "BottlePacking.h"
#include "Truck.h"

int main()
{
	Truck t;
	if (!initTruck(&t))
	{
		printf("error\n");
		return 0;
	}
	printTruck(&t);
	addPack(&t);
	printTruckContent(&t);
	freeTruck(&t);
}
