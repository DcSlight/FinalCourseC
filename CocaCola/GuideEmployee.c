#include "GuideEmployee.h"


static const char* EducationLevelStr[eNofEducationLevel]
= { "High School", "Academic", "Course" };

void initEmployeeGuide(Employee** pEmp, Employee** allEmployees, int employeesCount)//TODO: modify to pObj
{
	char* name;
	int age, seniority,id;
	eEducationLevel educationLevel;
	printf("Guide:\n");
	id = getUniqueId(allEmployees, employeesCount);
	name = getStrExactName("Enter employee name:");
	printf("Enter employee age - minimum %d:\t", MIN_AGE);
	do {
		scanf("%d", &age);
		if (age < MIN_AGE)
		{
			printf("Not a valid age, Try again\n");
		}
	} while (age < MIN_AGE);
	printf("Enter employee seniority:\t");
	do {
		scanf("%d", &seniority);
		if (seniority > age - MIN_AGE)
		{
			printf("Not a valid seniority years, Try again - maximum %d\t", age - MIN_AGE);
		}
	} while (seniority > age - MIN_AGE);
	printf("\n");
	educationLevel = getEducationLevel();
	*pEmp = newEmployeeGuide(name,id, age, eGuide, seniority, educationLevel);
}

eEducationLevel getEducationLevel()
{
	int option;
	do {
		printf("Please enter one of the following types\n");
		for (int i = 0; i < eNofEducationLevel; i++)
			printf("%d for %s\n", i, EducationLevelStr[i]);
		scanf("%d", &option);
	} while (option < 0 || option >= eNofEducationLevel);
	getchar();
	return (eEducationLevel)option;
}

Employee* newEmployeeGuide(const char* pName,const int id, const int age, const eEmployeeType type, int seniority, eEducationLevel educationLevel)
{
	EmployeeGuide* pEmpObj;
	Employee* pObj;
	pObj = newEmployee(pName,id, age, type, seniority);	//calling base class constructor
	//allocating memory
	pEmpObj = malloc(sizeof(EmployeeGuide));
	if (pEmpObj == NULL)
	{
		pObj->delete(pObj);
		return NULL;
	}
	pObj->pDerivedObj = pEmpObj; //pointing to derived object
	pEmpObj->educationLevel = educationLevel;
	//Changing base class interface to access derived class functions
	pObj->delete = deleteEmployeeGuide;
	pObj->print = printEmployeeGuide;
	pObj->writeBFile = writeGuideToBFile;
	pObj->writeTFile = writeGuideToTxtFile;
	pEmpObj->tellFact = tellFact;
	return pObj;
}

void deleteEmployeeGuide(Employee* const pEmployeeObj)
{
	EmployeeGuide* pEmpGuide;
	pEmpGuide = pEmployeeObj->pDerivedObj;
	free(pEmpGuide);
	freeEmployee(pEmployeeObj);
}

void printEmployeeGuide(Employee* const pEmployeeObj)
{
	printEmployee(pEmployeeObj);
	printf("\t\t\tType: Guide\t");
	EmployeeGuide* pEmpGuideObj;
	pEmpGuideObj = pEmployeeObj->pDerivedObj;
	printf("\tEducation: %-15s\n", EducationLevelStr[pEmpGuideObj->educationLevel]);
}

void tellFact(Employee* const pEmployeeObj,HistoricalEvent* pEvent)
{
	printHistoricalEvent(pEvent);
}


int writeGuideToBFile(FILE* fp, Employee* const pEmployeeObj)
{
	if (!writeEmployeeToBFile(fp, pEmployeeObj))
		return 0;
	EmployeeGuide* pEmpGuideObj;
	pEmpGuideObj = pEmployeeObj->pDerivedObj;
	if (!writeIntToFile(pEmpGuideObj->educationLevel, fp, "Error Writing Education Level Type\n"))
		return 0;
	return 1;
}

int readGuideFromBFile(FILE* fp, Employee** pEmployeeObj)
{
	if (!pEmployeeObj)
		return 0;
	int educationLevel;
	int id, age, seniority;
	char* name;
	if (!readEmployeeFromBFile(fp,&id,&age,&seniority,&name))
		return 0;
	if (!readIntFromFile(&educationLevel, fp, "Error reading Guide Education Level Type\n"))
		return 0;
	Employee* e = newEmployeeGuide(name,id,age, eGuide,seniority, educationLevel);
	free(name);
	*pEmployeeObj = e;//the new employeeGuide
	return 1;
}

int writeGuideToTxtFile(FILE* fp, Employee* const pEmployeeObj)
{
	if (!writeEmployeeToTxtFile(fp, pEmployeeObj))
		return 0;
	EmployeeGuide* pEmpGuideObj;
	pEmpGuideObj = pEmployeeObj->pDerivedObj;
	fprintf(fp, "%d\n", pEmpGuideObj->educationLevel);
	return 1;
}

int readGuideFromTxtFile(FILE* fp, Employee** pEmployeeObj) 
{
	if (!pEmployeeObj)
		return 0;
	int educationLevel;
	int id, age, seniority;
	char* name;
	if (!readEmployeeFromTxtFile(fp, &id, &age, &seniority, &name))
		return 0;
	if (fscanf(fp, "%d", &educationLevel) != 1)
		return 0;
	Employee* e = newEmployeeGuide(name, id, age, eGuide, seniority, educationLevel);
	free(name);
	*pEmployeeObj = e;//the new employeeGuide
	return 1;
}
