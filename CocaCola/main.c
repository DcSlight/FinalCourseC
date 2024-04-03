#include <stdio.h>
#include <time.h>
#include "CocaColaFactory.h"
#include "CocaColaFunctions.h"

int main()
{
    srand((unsigned)time(NULL));
    printLOGO();
    cocaColaLinkWebsite();
    FILE* fp;
   //Employee* e = newEmployeeDriver("idan", 1, 25, eDriver, 3, eC1);
    Employee e;
    fp = fopen("emD.bin", "rb");
    readDriverFromBFile(fp,&e);
    ////writeDriverToBFile(fp, e);
    //fclose(fp);
    //printEmployeeDriver(&e);
   // e.print(&e);
  //  fp = fopen("emD.txt", "r");
 //   e->writeTFile(fp, e);
 //   readDriverFromTxtFile(fp, &e);
    fclose(fp);
    printEmployeeDriver(&e);
   // e.print(&e);

    return 0;
}
