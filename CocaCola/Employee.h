#ifndef __EMPLOYEE__
#define __EMPLOYEE__


typedef struct
{
	char* name;
	int age;
}Employee;

void initEmployee(Employee* pEmp);
void printEmployee(const Employee* pEmp);
void freeEmployee(Employee* pEmp);

#endif /* __EMPLOYEE__ */