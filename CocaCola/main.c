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
#include "HistoricalEvent.h"

int main()
{
	FILE* fp = fopen("try.txt", "r");
	HistoricalEvent e;
	//initHistoricalEvent(&e);
	readEventFromTxtFile(fp, &e);
	//writeEventToTxtFile(fp, &e);
	fclose(fp);
	printHistoricalEvent(&e);
}
