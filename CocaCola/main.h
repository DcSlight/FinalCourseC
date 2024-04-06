#ifndef __MAIN__
#define __MAIN__

#include "CocaColaFactory.h"

#define EXIT -1
#define FACTORY_B_FILE_NAME "Coca_Cola_Factory.bin"
#define FACTORY_TXT_FILE_NAME "Coca_Cola_Factory.txt"
#define EVENTS_B_FILE_NAME "Historical_Events.bin"
#define EVENTS_TXT_FILE_NAME "Historical_Events.txt"
#define ERROR 0
#define FROM_BIN_FILE 1
#define FROM_TXT_FILE 2
#define FROM_USER 3

typedef enum
{
	eEmployeesMenu, eSuppliersMenu, eTrucksMenu, eAddHistoricalEvent, eToursMenu,
	ePrintFactory, eFindSecretRecipe, eNofOptions
} eMainMenuOptions;

const char* str[eNofOptions] = { "Employees Menu","Suppliers Menu","Trucks Menu",
								"Add a historical event", "Tours Menu",
								"Print Coca Cola Factory",
								"Find Secret Recipe" };

void initCocaColaFactory(CocaColaFactory* pFactory);
int mainMenu();
void employeesMenu(CocaColaFactory* pFactory);
void suppliersMenu(CocaColaFactory* pFactory);
void TrucksMenu(CocaColaFactory* pFactory);
void ToursMenu(CocaColaFactory* pFactory);

#endif
