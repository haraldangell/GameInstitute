#pragma once
#include <iostream>
#include <string>
#include <fstream>


class Employee
{
public:
	Employee();
	Employee(std::string firstname, std::string lastname, int salary);
	virtual void save(std::ofstream& out) const = 0;
	virtual void Print() const = 0;
	virtual ~Employee();

protected:
	std::string mFirstName;
	std::string mLastName;
	int mSalary;
};

