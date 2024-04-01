#ifndef DATETIME_H_
#define DATETIME_H_

#define MIN_YEAR 2024

typedef struct
{
	unsigned hour;
	unsigned min;
}Time;

typedef struct
{
	unsigned day;
	unsigned month;
	unsigned year;
} Date;

typedef struct
{
	Time theTime;
	Date theDate;
} DateTime;

void initDateTime(DateTime* pDateTime);
void getCorrectDate(Date* pDate);
int	 checkDate(char* date, Date* pDate);
void getCorrectTime(Time* pTime);
int	checkTime(char* time, Time* pTime);
void printDateTime(const DateTime* pDateTime);
int	compareDateTimebyDate(const void* d1, const void* d2);
int	compareDateTimebyTime(const void* t1, const void* t2);
int compareDateTime(const void* dt1, const void* dt2);

int writeDateToBFile(FILE* fp, const Date* pDate);
int writeTimeToBFile(FILE* fp, const Time* pTime);
int writeDateTimeToBFile(FILE* fp, const DateTime* pDateTime);
int writeDateTimeToTxtFile(FILE* fp, const DateTime* pDateTime);

int readDateFromBFile(FILE* fp, Date* pDate);
int readTimeFromBFile(FILE* fp, Time* pTime);
int readDateTimeFromBFile(FILE* fp, DateTime* pDateTime);
int readDateTimeFromTxtFile(FILE* fp, DateTime* pDateTime);

#endif /* DATETIME_H_ */