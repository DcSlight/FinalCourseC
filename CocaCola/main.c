#include <stdio.h>
#include <time.h>
#include "CocaColaFactory.h"

int main()
{
    //int x = 1;
    //switch (x)
    //{
    //case 1:
    //    #define B_FILE 1
    //    break;
    //default:
    //    break;
    //}


    srand((unsigned)time(NULL));
    CocaColaFactory factory;
    initFactory(&factory);
    addTruck(&factory);
    addTruck(&factory);
    printTrucksArr(&factory);


  //  addTour(&factory);


  //  addEventToFactory(&factory);
  //  addEventToFactory(&factory);
  //  addEventToFactory(&factory);
  //  addEventToFactory(&factory);
  //  addEventToFactory(&factory);
  //  L_print(&factory.allEvents,printHistoricalEvent);


  //  


  //  CocaColaTour pTour;
  //  initCocaColaTour(&pTour,"try.bin");
  ////  fillEventsFromBFile(&pTour, "try.bin",factory.allEvents);
  //  startTour(&pTour);
  //  printf("\n_____\n");
  //  L_print(&factory.allEvents, printHistoricalEvent);
  //  printf("\n_____\n");
  //  freeCocaColaTour(&pTour);
  //  L_print(&factory.allEvents, printHistoricalEvent);
    return 0;
}
