#pragma once
#include "Employee.h"
#include <fstream>

class Manager :
	public Employee
{
public:
	Manager();
	Manager(std::string firstname, std::string lastname, int salary, int meetings, int vacation);
	~Manager();

	// Inherited via Employee
	virtual void save(std::ofstream& out) const override;
	virtual void Print() const override;

protected:
	int mNumberOfMeetingPerWeek;
	int mNumberOfVacationDaysPerYear;



};

