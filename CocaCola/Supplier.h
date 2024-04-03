#ifndef __SUPPLIER__
#define __SUPPLIER__

#include "Address.h"

#define PHONE_LEN 15

typedef struct
{
	int id;
	char* name;
	char phoneNo[PHONE_LEN];
	Address address;
} Supplier;

void initSupplier(Supplier* pSupplier, Supplier** allSuppliers, int suppliersCount);
void getSupplierId(Supplier* pSupplier, Supplier** allSuppliers, int suppliersCount);
void printSupplier(const Supplier* pSupplier);
void freeSupplier(Supplier* pSupplier);

int writeSupplierToBFile(FILE* fp, const Supplier* pSupplier);
int readSupplierFromBFile(FILE* fp, Supplier* pSupplier);

#endif /* __SUPPLIER__ */
