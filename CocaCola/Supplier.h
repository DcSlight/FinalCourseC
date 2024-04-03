#ifndef __SUPPLIER__
#define __SUPPLIER__

#include <ctype.h>
#include "Address.h"

#define PHONE_LEN 10

typedef struct
{
	int id;
	char* name;
	char phoneNo[PHONE_LEN + 1];
	Address address;
} Supplier;

void initSupplier(Supplier* pSupplier, Supplier** allSuppliers, int suppliersCount);
void getSupplierId(Supplier* pSupplier, Supplier** allSuppliers, int suppliersCount);
void getSupplierPhone(char* phoneNumber);
void printSupplier(const Supplier* pSupplier);
void freeSupplier(Supplier* pSupplier);

int writeSupplierToBFile(FILE* fp, const Supplier* pSupplier);
int readSupplierFromBFile(FILE* fp, Supplier* pSupplier);

int writeSupplierToTxtFile(FILE* fp, const Supplier* pSupplier);
int readSupplierFromTxtFile(FILE* fp, Supplier* pSupplier);

#endif /* __SUPPLIER__ */
