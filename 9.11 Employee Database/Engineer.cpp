#include "Engineer.h"



Engineer::Engineer()
{
	std::cout << "Do the person know C++? (1) Yes (0) No: ";
	std::cin >> mKnowCPP;
	std::cout << "How many years of experience does the person have? ";
	std::cin >> mYearsOfExperience;
	std::cout << "What type of engineer is the person? ";
	std::cin >> mWhatTypeOfEngineer;
}

Engineer::Engineer(std::string firstname, std::string lastname, int salary, bool knowcpp, int yearofexp, std::string typeofeng)
	: Employee(firstname, lastname, salary)
{
	mKnowCPP = knowcpp;
	mYearsOfExperience = yearofexp;
	mWhatTypeOfEngineer = typeofeng;
}


Engineer::~Engineer()
{
}

void Engineer::save(std::ofstream & out) const
{
	if (out)
	{
		out << "Engineer" << std::endl;
		out << "==========" << std::endl;
		out << mFirstName << std::endl;
		out << mLastName << std::endl;
		out << mSalary << std::endl;
		out << mKnowCPP << std::endl;
		out << mYearsOfExperience << std::endl;
		out << mWhatTypeOfEngineer << std::endl;

	}
}

void Engineer::Print() const
{
	std::cout << "Engineer" << std::endl;
	std::cout << "**********" << std::endl;
	std::cout << mFirstName << std::endl;
	std::cout << mLastName<< std::endl;
}
