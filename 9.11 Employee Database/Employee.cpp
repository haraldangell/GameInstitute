#include "Employee.h"



Employee::Employee()
{
	std::cout << "What is the firstname: ";
	std::cin >> mFirstName;
	std::cout << "What is the lastname: ";
	std::cin >> mLastName;
	std::cout << "What is the salary: ";
	std::cin >> mSalary;
}

Employee::Employee(std::string firstname, std::string lastname, int salary)
{
	mFirstName = firstname;
	mLastName = lastname;
	mSalary = salary;
}




Employee::~Employee()
{
}
