#include <stdio.h>
#include <time.h>
#include "CocaColaFactory.h"
#include "CocaColaFunctions.h"
#include "CocaColaFactoryFile.h"

int main()
{
    //srand((unsigned)time(NULL));
    /*unsigned seed = (unsigned)time(NULL);
    srand(seed);*/
    printLOGO();
    cocaColaLinkWebsite();
    CocaColaFactory f;

    initFactory(&f);

    printFactory(&f);



    //addEmployee(&f);
    //saveFactoryToTxtFile(&f, "factoryTry.txt", "eventTry.txt");
   // initFactoryFromBFile(&f, "fac.bin");
  //  printFactory(&f); 
   // addEventToFactory(&f);
   // addEventToFactory(&f);
  //  addEventToFactory(&f);
  //  writeEventsListToBFile(&f, "allEventsB.bin");
   // readEventsListFromBFile(&f, "allEventsB.bin");
  //  L_print(&f.allEvents, printHistoricalEvent);


    /*initFactory(&f);
    addEmployee(&f);
    addEmployee(&f);
    addSupplier(&f);
    addSupplier(&f);
    addTruck(&f);
    addTruck(&f);
    addPack(&f.trucks[0]);
    saveFactoryToBFile(&f, "fac.bin");*/
   // saveFactoryFromTxtFile(&f, "f.txt");
    return 0;
}
