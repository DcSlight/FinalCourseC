#include <stdio.h>
#include <time.h>
#include "CocaColaFactory.h"
#include "CocaColaFunctions.h"

int main()
{
    srand((unsigned)time(NULL));
    printLOGO();
    cocaColaLinkWebsite();
    Supplier s;
    FILE* fp;

    fp = fopen("supplierTry.txt", "r");
    //initSupplier(&s, NULL, 0);
    //writeSupplierToTxtFile(fp, &s);
    readSupplierFromTxtFile(fp, &s);
    printSupplier(&s);
    fclose(fp);

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
