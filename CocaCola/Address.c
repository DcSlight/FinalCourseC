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

int writeAddressToTxtFile(FILE* fp, const Address* pAddress)
{
	if (!pAddress)
		return 0;
	fprintf(fp, "%s\n", pAddress->city);
	fprintf(fp, "%s\n", pAddress->street);
	fprintf(fp, "%d\n", pAddress->houseNo);
	return 1;
}

int readAddressFromTxtFile(FILE* fp, Address* pAddress)
{
	char temp[MAX_STR_LEN];
	if (!pAddress)
		return 0;

	myGets(temp, MAX_STR_LEN, fp);
	pAddress->city = getDynStr(temp);

	myGets(temp, MAX_STR_LEN, fp);
	pAddress->street = getDynStr(temp);

	int tempHouseNo;
	if (fscanf(fp, "%d", &tempHouseNo) != 1)
		return 0;
	pAddress->houseNo = tempHouseNo;
	return 1;
}




