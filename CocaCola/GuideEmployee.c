#include "GuideEmployee.h"


static const char* EducationLevelStr[eNofEducationLevel]
= { "High School", "Academic", "Course" };

void initEmployeeGuide(Employee** pEmp)
{
	char* name;
	int age, seniority;
	eEducationLevel educationLevel;
	name = getStrExactName("Enter employee name:");
	printf("Enter employee age:\t");
	scanf("%d", &age);
	printf("Enter employee seniority:\t");
	scanf("%d", &seniority);
	printf("\n");
	educationLevel = getEducationLevel();
	*pEmp = newEmployeeGuide(name, age, eGuide, seniority, educationLevel);
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

Employee* newEmployeeGuide(const char* pName, const int age, const eEmployeeType type, int seniority, eEducationLevel educationLevel)
{
	EmployeeGuide* pEmpObj;
	Employee* pObj;
	pObj = newEmployee(pName, age, type, seniority);	//calling base class constructor
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
	pEmpObj->tellFact = tellFact;
	return pObj;
}

void deleteEmployeeGuide(Employee* const pEmployeeObj)
{
	freeEmployee(pEmployeeObj);
}

void printEmployeeGuide(Employee* const pEmployeeObj)
{
	printEmployee(pEmployeeObj);
	printf("Type: Guide\n");
	EmployeeGuide* pEmpGuideObj;
	pEmpGuideObj = pEmployeeObj->pDerivedObj;
	printf("Education Level: %s\n", EducationLevelStr[pEmpGuideObj->educationLevel]);
}

void tellFact(Employee* const pEmployeeObj)
{
	printf("hello world!\n");
}
