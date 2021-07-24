#pragma once
#include "Employee.h"
#include <fstream>

class Engineer : public Employee
{
public:
	Engineer();
	Engineer(std::string firstname, std::string lastname, int salary, bool knowcpp, int yearofexp, std::string typeofeng);
	~Engineer();

	// Inherited via Employee
	virtual void save(std::ofstream & out) const override;
	virtual void Print() const override;

protected:
	bool mKnowCPP;
	int mYearsOfExperience;
	std::string mWhatTypeOfEngineer;
};

/*
1. A value specifying whether or not they know C++.
2. Number of years of experience.
3. A string denoting the type of engineer they are (e.g., “mechanical,” “electric,”
“software.”

*/