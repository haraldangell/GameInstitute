#pragma once
#include "Employee.h"
#include <fstream>
class Researcher :	public Employee
{
public:
	Researcher();
	Researcher(std::string firstname, std::string lastname, int salary, std::string school, std::string thesis);
	~Researcher();

	// Inherited via Employee
	virtual void save(std::ofstream & out) const override;
	virtual void Print() const override;
protected:
	std::string mSchoolReceivedPHD;
	std::string mWhatTopicOfThesis;
};

