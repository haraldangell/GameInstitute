#include "Researcher.h"



Researcher::Researcher()
{
	std::cout << "What school did the person received his/her Phd from? ";
    std::cin >> mSchoolReceivedPHD;
	std::cout << "What was the topic of the PHD thesis? ";
	std::cin >>	mWhatTopicOfThesis;
}

Researcher::Researcher(std::string firstname, std::string lastname, int salary, std::string school, std::string thesis)
	: Employee(firstname, lastname, salary)
{
	mSchoolReceivedPHD = school;
	mWhatTopicOfThesis = thesis;
}


Researcher::~Researcher()
{
}

void Researcher::save(std::ofstream & out) const
{
	if (out)
	{
		out << "Researcher" << std::endl;
		out << "==========" << std::endl;
		out << mFirstName << std::endl;
		out << mLastName << std::endl;
		out << mSalary << std::endl;
		out << mSchoolReceivedPHD << std::endl;
		out << mWhatTopicOfThesis << std::endl;
	}
}

void Researcher::Print() const
{
	std::cout << "Researcher" << std::endl;
	std::cout << "**********" << std::endl;
	std::cout << mFirstName << std::endl;
	std::cout << mLastName << std::endl;
}
