#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Address.h"
#include "General.h"

void initAddress(Address* pAddress)
{
	printf("");
	pAddress->city = getStrExactName("Enter a city:");
	pAddress->street = getStrExactName("Enter a street:");
	printf("Enter a house number:\t");
	scanf("%d", &pAddress->houseNo);
}

void printAddress(const Address* pAddress)
{
	printf("Address: %s %d, %s\n", pAddress->street, pAddress->houseNo, pAddress->city);
}

void freeAddress(Address* pAddress)
{
	free(pAddress->city);
	free(pAddress->street);
}




