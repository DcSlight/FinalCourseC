#include <stdio.h>
#include <time.h>
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
#include "CocaColaTour.h"

int main()
{
    srand((unsigned)time(NULL));
    CocaColaTour pTour;
    initCocaColaTour(&pTour,"try.bin");
    fillEvents(&pTour, "try.bin");
    startTour(&pTour);
    return 0;
}
