#ifndef __ADDRESS__
#define __ADDRESS__

typedef struct
{
	char* city;
	char* street;
	int houseNo;
} Address;

void initAddress(Address* pAddress);
void printAddress(const Address* pAddress);
void freeAddress(Address* pAddress);

int writeAddressToTxtFile(FILE* fp, const Address* pAddress);
int writeAddressToBFile(FILE* fp, const Address* pAddress);


int readAddressFromTxtFile(FILE* fp, Address* pAddress);


#endif /* __ADDRESS__ */