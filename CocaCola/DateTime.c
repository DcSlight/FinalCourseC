#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "DateTime.h"
#include "General.h"


const unsigned DAY_MONTHS[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
#define SPECIAL_DATE_TAV '/'
#define SPECIAL_TIME_TAV ':'

void initDateTime(DateTime* pDateTime)
{
	Date pDate;
	Time pTime;
	getCorrectDate(&pDate);
	getCorrectTime(&pTime);
	pDateTime->theDate = pDate;
	pDateTime->theTime = pTime;
}

void getCorrectDate(Date* pDate)
{
	char date[MAX_STR_LEN];
	int ok = 1;

	do {
		printf("Enter a date in the format dd%cmm%cyyyy and minimum year %d\t",
			SPECIAL_DATE_TAV, SPECIAL_DATE_TAV, MIN_YEAR);
		myGets(date, MAX_STR_LEN, stdin);
		ok = checkDate(date, pDate);
		if (!ok)
			printf("Error try again\n");
	} while (!ok);
}


int	 checkDate(char* date, Date* pDate)
{
	unsigned day, month, year;
	if (strlen(date) != 10)
		return 0;
	if ((date[2] != SPECIAL_DATE_TAV) || (date[5] != SPECIAL_DATE_TAV))
		return 0;
	sscanf(date, "%u%*c%u%*c%u", &day, &month, &year);
	if (day < 1 || month < 1 || month > 12 || year < MIN_YEAR)
		return 0;

	if (day > DAY_MONTHS[month - 1])
		return 0;

	pDate->day = day;
	pDate->month = month;
	pDate->year = year;

	return 1;
}

void getCorrectTime(Time* pTime)
{
	char time[MAX_STR_LEN];
	int ok = 1;

	do {
		printf("Enter a time in the format hh%cmm\t",
			SPECIAL_TIME_TAV);
		myGets(time, MAX_STR_LEN, stdin);
		ok = checkTime(time, pTime);
		if (!ok)
			printf("Error try again\n");
	} while (!ok);
}

int checkTime(char* time, Time* pTime)
{
	unsigned hour, min;
	if (strlen(time) != 5)
		return 0;
	if (time[2] != SPECIAL_TIME_TAV)
		return 0;
	sscanf(time, "%u%*c%u", &hour, &min);

	if (hour < 0 || min < 0 || hour > 23 || min > 59)
		return 0;

	pTime->hour = hour;
	pTime->min = min;

	return 1;
}

void printDateTime(const DateTime* pDateTime)
{
	printf("Date: %u%c%u%c%u\tTime: %02u%c%02u\n", pDateTime->theDate.day, SPECIAL_DATE_TAV, pDateTime->theDate.month,
		SPECIAL_DATE_TAV, pDateTime->theDate.year, pDateTime->theTime.hour, SPECIAL_TIME_TAV, pDateTime->theTime.min);
}

int	compareDateTimebyDate(const void* d1, const void* d2)
{
	const Date* pDate1 = (const Date*)d1;
	const Date* pDate2 = (const Date*)d2;
	if (pDate1->year > pDate2->year)
		return 1;
	if (pDate1->year < pDate2->year)
		return -1;

	if (pDate1->month > pDate2->month)
		return 1;

	if (pDate1->month < pDate2->month)
		return -1;

	if (pDate1->day > pDate2->day)
		return 1;

	if (pDate1->day < pDate2->day)
		return -1;

	return 0;
}

int	compareDateTimebyTime(const void* t1, const void* t2)
{
	const Time* pTime1 = (const Time*)t1;
	const Time* pTime2 = (const Time*)t2;
	if (pTime1->hour > pTime2->hour)
		return 1;
	if (pTime1->hour < pTime2->hour)
		return -1;
	if (pTime1->min > pTime2->min)
		return 1;
	if (pTime1->min < pTime2->min)
		return -1;

	return 0;
}


