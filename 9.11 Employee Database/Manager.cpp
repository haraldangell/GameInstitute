#include "Manager.h"
#include <fstream>


Manager::Manager()
{
	std::cout << "How many meetings do the person have per week? ";
	std::cin >> mNumberOfMeetingPerWeek;
	std::cout << "How many vacation days have the person per year? ";
	std::cin >> mNumberOfVacationDaysPerYear;
}

Manager::Manager(std::string firstname, std::string lastname, int salary, int meetings, int vacation)
	: Employee(firstname, lastname, salary)
{
	mNumberOfMeetingPerWeek = meetings;
	mNumberOfVacationDaysPerYear = vacation;
}


Manager::~Manager()
{
}

void Manager::save(std::ofstream& out) const
{
	if (out)
	{
		out << "Manager" << std::endl;
		out << "==========" << std::endl;
		out << mFirstName << std::endl;
		out << mLastName << std::endl;
		out << mSalary << std::endl;
		out << mNumberOfMeetingPerWeek << std::endl;
		out << mNumberOfVacationDaysPerYear << std::endl;

	}
}

void Manager::Print() const
{
	std::cout << "Manager" << std::endl;
	std::cout << "**********" << std::endl;
	std::cout << mFirstName << std::endl;
	std::cout << mLastName << std::endl;
}
