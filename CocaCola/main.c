#include <stdio.h>
#include <time.h>
#include "main.h"
#include "CocaColaFunctions.h"
#include "CocaColaFactoryFile.h"
#include <crtdbg.h>

int main()
{
    printLOGO();
    cocaColaLinkWebsite();
    CocaColaFactory factory;
    initCocaColaFactory(&factory);

    int option;
    int stop = 0;

    do
    {
        option = mainMenu();
        switch (option)
        {
        case eEmployeesMenu:
            employeesMenu(&factory);
;            break;
        case eSuppliersMenu:
            suppliersMenu(&factory);
            break;
        case eTrucksMenu:
            TrucksMenu(&factory);
            break;
        case eAddHistoricalEvent:
            addEventToFactory(&factory);
            break;
        case eToursMenu:
            ToursMenu(&factory);
            break;
        case ePrintFactory:
            printFactory(&factory);
            break;
        case eFindSecretRecipe:
            findSecretRecipe();
            break;
        case EXIT:
            printf("Bye bye\n");
            stop = 1;
            break;
        default:
            printf("Not a valid option\n");
            break;
        }
    } while (!stop);

    if (!saveFactoryToBFile(&factory, FACTORY_B_FILE_NAME, EVENTS_B_FILE_NAME))
    {
        printf("Error saving factory to binary file\n");
    }
    if (!saveFactoryToTxtFile(&factory, FACTORY_TXT_FILE_NAME, EVENTS_TXT_FILE_NAME))
    {
        printf("Error saving factory to text file\n");
    }

    freeFactory(&factory);
 
    return 0;
}

void initCocaColaFactory(CocaColaFactory* pFactory)
{
    int option;
    printf(ANSI_COLOR_CYAN"\n---------------------------------------------------\n"ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "\t  Welcome To Coca Cola Factory\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN"---------------------------------------------------\n\n"ANSI_COLOR_RESET);
    do
    {
        printf("Choose how to initial Coca Cola Factory\n");
        printf("1 - From binary file\n");
        printf("2 - From text file\n");
        printf("3 - From user\n");
        scanf("%d", &option);
        switch (option)
        {
        case FROM_BIN_FILE:
            initFactoryFromBFile(pFactory, FACTORY_B_FILE_NAME, EVENTS_B_FILE_NAME);
            break;
        case FROM_TXT_FILE:
            initFactoryFromTxtFile(pFactory, FACTORY_TXT_FILE_NAME, EVENTS_TXT_FILE_NAME);
            break;
        case FROM_USER:
            initFactory(pFactory);
            break;
        default:
            option = ERROR;
            printf("Not a valid option\n");
            break;
        }
    } while (option == ERROR);
}

int mainMenu()
{
    int option;
    printf(ANSI_COLOR_CYAN"\n---------------------------------------------------\n"ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "\t\t  Main Menu\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN"---------------------------------------------------\n\n"ANSI_COLOR_RESET);
    printf("Please choose one of the following options\n");
    for (int i = 0; i < eNofOptions; i++)
        printf("%d - %s\n", i, str[i]);
    printf("%d - Quit\n", EXIT);
    scanf("%d", &option);
    //clean buffer
    char tav;
    scanf("%c", &tav);
    return option;
}

void employeesMenu(CocaColaFactory* pFactory)
{
    int option;
    int stop = 0;
    printf(ANSI_COLOR_CYAN"\n---------------------------------------------------\n"ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "\t\t  Employees Menu\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN"---------------------------------------------------\n"ANSI_COLOR_RESET);
    do
    {
        printf("\nPlease choose one of the following options\n");
        printf("1 - Add an employee\n");
        printf("2 - Print all employees\n");
        printf("3 - Back to main menu\n");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            if (!addEmployee(pFactory))
                printf("Error adding Employee\n");
            break;
        case 2:
            printEmployeesArr(pFactory->employees, pFactory->employeesCount);
            break;
        case 3:
            stop = 1;
            break;
        default:
            option = ERROR;
            printf("Not a valid option\n");
            break;
        }
    } while (option == ERROR || !stop);
}

void suppliersMenu(CocaColaFactory* pFactory)
{
    int option;
    int stop = 0;
    printf(ANSI_COLOR_CYAN"\n---------------------------------------------------\n"ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "\t\t  Suppliers Menu\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN"---------------------------------------------------\n"ANSI_COLOR_RESET);
    do
    {
        printf("\nPlease choose one of the following options\n");
        printf("1 - Add a supplier\n");
        printf("2 - Print all suppliers\n");
        printf("3 - Back to main menu\n");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            if (!addSupplier(pFactory))
                printf("Error adding Supplier\n");
            break;
        case 2:
            printSuppliersArr(pFactory->suppliers, pFactory->suppliersCount);
            break;
        case 3:
            stop = 1;
            break;
        default:
            option = ERROR;
            printf("Not a valid option\n");
            break;
        }
    } while (option == ERROR || !stop);
}

void TrucksMenu(CocaColaFactory* pFactory)
{
    int option;
    int stop = 0;
    printf(ANSI_COLOR_CYAN"\n---------------------------------------------------\n"ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "\t\t  Trucks Menu\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN"---------------------------------------------------\n"ANSI_COLOR_RESET);
    do
    {
        printf("\nPlease choose one of the following options\n");
        printf("1 - Add a Truck\n");
        printf("2 - Add a pack to truck\n");
        printf("3 - Print all trucks\n");
        printf("4 - Print content in a truck\n");
        printf("5 - Back to main menu\n");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            if (!addTruck(pFactory))
                printf("Error adding a truck\n");
            break;
        case 2:
            addPackToTruck(pFactory);
            break;
        case 3:
            printTrucksArr(pFactory->trucks, pFactory->trucksCount);
            break;
        case 4:
            doPrintTruckContent(pFactory);
            break;
        case 5:
            stop = 1;
            break;
        default:
            option = ERROR;
            printf("Not a valid option\n");
            break;
        }
    } while (option == ERROR || !stop);
}

void ToursMenu(CocaColaFactory* pFactory)
{
    int option;
    int stop = 0;
    printf(ANSI_COLOR_CYAN"\n---------------------------------------------------\n"ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "\t\t  Tours Menu\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN"---------------------------------------------------\n"ANSI_COLOR_RESET);
    do
    {
        printf("\nPlease choose one of the following options\n");
        printf("1 - Add a Tour\n");
        printf("2 - Start a Tour\n");
        printf("3 - Print all tours\n");
        printf("4 - Sort tours\n");
        printf("5 - Find a tour\n");
        printf("6 - Back to main menu\n");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            if (!addTour(pFactory))
                printf("Error adding a tour\n");
            break;
        case 2:
            EnterTour(pFactory);
            break;
        case 3:
            printTours(pFactory->tours, pFactory->toursCount);
            break;
        case 4:
            sortTours(pFactory);
            break;
        case 5:
            findTour(pFactory);
            break;
        case 6:
            stop = 1;
            break;
        default:
            option = ERROR;
            printf("Not a valid option\n");
            break;
        }
    } while (option == ERROR || !stop);
}
