#include <stdio.h>
#include <time.h>
#include "CocaColaFactory.h"

int main()
{
    srand((unsigned)time(NULL));
    CocaColaFactory factory;
    initFactory(&factory);
    addEventToFactory(&factory);
    addEventToFactory(&factory);
    addEventToFactory(&factory);
    addEventToFactory(&factory);
    addEventToFactory(&factory);
    L_print(&factory.allEvents,printHistoricalEvent);


    


    CocaColaTour pTour;
    initCocaColaTour(&pTour,"try.bin");
    fillEvents(&pTour, "try.bin",factory.allEvents);
    startTour(&pTour);
    printf("\n_____\n");
    L_print(&factory.allEvents, printHistoricalEvent);
    printf("\n_____\n");
    freeCocaColaTour(&pTour);
    L_print(&factory.allEvents, printHistoricalEvent);
    return 0;
}
