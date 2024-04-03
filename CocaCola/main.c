#include <stdio.h>
#include <time.h>
#include "CocaColaFactory.h"
#include "CocaColaFunctions.h"

int main()
{
    srand((unsigned)time(NULL));
    printLOGO();
    cocaColaLinkWebsite();
   // BottlePacking bp;
    FILE* fp;

    Bottle b;
    initBottle(&b);
    fp = fopen("bottle.bin", "wb");
    writeBottleToBFileCompress(fp, &b);

    fclose(fp);
    fp = fopen("bottle.bin", "rb");
    readBottleFromBFileCompress(fp, &b);
    fclose(fp);
    printBottle(&b);
   /* CocaColaFactory factory;
    initFactory(&factory);
    addEmployee(&factory);
    addEventToFactory(&factory);
    addTour(&factory);*/


    /*printf("------------------------\n");
    addTour(&factory);
    addEventToFactory(&factory);
    printf("------------------------\n");
    addTour(&factory);
    addEventToFactory(&factory);
    printf("------------------------\n");
    EnterTour(&factory);*/


  //  addTour(&factory);


  //  addEventToFactory(&factory);
  //  addEventToFactory(&factory);
  //  addEventToFactory(&factory);
  //  addEventToFactory(&factory);
  //  addEventToFactory(&factory);
  //  L_print(&factory.allEvents,printHistoricalEvent);


  //  


  //  CocaColaTour pTour;
   // initCocaColaTour(&pTour,"try.bin");
  //  fillEventsFromBFile(&pTour, "try.bin",factory.allEvents);
  //  startTour(&pTour);
  //  printf("\n_____\n");
  //  L_print(&factory.allEvents, printHistoricalEvent);
  //  printf("\n_____\n");
  //  freeCocaColaTour(&pTour);
  //  L_print(&factory.allEvents, printHistoricalEvent);
    return 0;
}
