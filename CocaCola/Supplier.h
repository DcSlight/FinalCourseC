#ifndef __SUPPLIER__
#define __SUPPLIER__

#include "Address.h"

#define PHONE_LEN 15

typedef struct
{
	char* name;
	char phoneNo[PHONE_LEN];
	Address address;
} Supplier;

void initSupplier(Supplier* pSupplier);
void printSupplier(const Supplier* pSupplier);
void freeSupplier(Supplier* pSupplier);

#endif /* __SUPPLIER__ */
