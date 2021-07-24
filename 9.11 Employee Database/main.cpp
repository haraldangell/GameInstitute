#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Employee.h"
#include "Manager.h"
#include "Engineer.h"
#include "Researcher.h"

using namespace std;


void Add(vector<Employee*>& Emp);
void Delete(vector<Employee*>& Emp);
void Save(vector<Employee*>& Emp, string str);
void Load(vector<Employee*>& Emp, string str);

int main()
{
	vector<Employee*> Emp;
	string str = "Data.txt";

	bool quit = false;
	cout << "*******************************" << endl;
	cout << "Welcome to Employee Database!!!" << endl;
	cout << "*******************************" << endl;
	while(!quit)
	{
		int selection = 0;
		cout << "1) Add an Employee, 2) Delete an Employee 3) Save Database, 4) Load Database 5) Populate Database 6) List Database 7) Exit.";
		cin >> selection;
		switch (selection)
		{
		case 1:
			Add(Emp);
			break;
		case 2:
			Delete(Emp);
			break;
		case 3:
			Save(Emp, str);
			break;
		case 4:
			Load(Emp, str);
			break;
		case 5:
			Emp.push_back(new Manager("F1","L1", 23, 45, 23));
			Emp.push_back(new Manager("F2", "L2", 23, 45, 23));
			Emp.push_back(new Engineer("F3", "L4", 23, 1, 10, "Software"));
			Emp.push_back(new Researcher("F45", "L453", 23, "Havard UNI", "AI"));
			break;
		case 6:
			cout << "Listing all employees!" << endl;
			for (int i = 0; i < Emp.size(); ++i)
			{
				cout << "Employee id number: " << i << ") " << endl;
				Emp[i]->Print();
			}
			break;
		case 7:
			quit = true;
			cout << "Exiting....." << endl;
			break;
		}
	}

	return 0;
}

void Add(vector<Employee*>& Emp)
{
	int selection = 0;
	cout << "1) Manager, 2) Engineer 3) Researcher, 4) Exit.";
	cin >> selection;

	switch (selection)
	{
	case 1:
		Emp.push_back(new Manager);
		break;
	case 2:
		Emp.push_back(new Engineer);
		break;
	case 3:
		Emp.push_back(new Researcher);
		break;
	case 4:
		break;
	}

}

void Delete(vector<Employee*>& Emp)
{
	int selection = 0;
	cout << "1) List employees 2) Delete Employee: " << endl;
	cin >> selection;
	switch (selection)
	{
	case 1:
		cout << "Listing all employees!" << endl;
		for (int i = 0; i < Emp.size(); ++i)
		{
			cout << "Employee id number: " << i << ") " << endl;
			Emp[i]->Print();
		}
		break;
	case 2:
		int sel;
		cout << "What is the employee id? ";
		cin >> sel;

		char yesno = 'a';
		Emp[sel]->Print();
		cout << "Sure you want to delete this employee? Y/N " << endl;

		cin >> yesno;
		if (yesno == 'y' || yesno == 'Y')
			Emp.erase(Emp.begin() + sel);
		break;

	}




}

void Save(vector<Employee*>& Emp, string str)
{
	ofstream out(str);
	if (out)
	{
		for (int i = 0; i < Emp.size(); ++i)
			Emp[i]->save(out);
		out.close();
	}
}

void Load(vector<Employee*>& Emp, string str)
{
	Emp.clear();
	ifstream in(str);
	if (in)
	{
		while (!in.eof())
		{
			string type, garbage, firstname, lastname; 
			int salary;
			in >> type;
			in >> garbage;
			in >> firstname;
			in >> lastname;
			in >> salary;

			if (type == "Manager")
			{
				int meetings, vacation;
				in >> meetings;
				in >> vacation;
				Emp.push_back(new Manager(firstname, lastname, salary, meetings, vacation));
			}
			else if (type == "Engineer")
			{
				bool knowcpp;
				int yearexp;
				string typeeng;
				in >> knowcpp;
				in >> yearexp;
				in >> typeeng;
				Emp.push_back(new Engineer(firstname, lastname, salary, knowcpp, yearexp, typeeng));
			}
			else if (type == "Researcher")
			{
				string school, thesis;
				in >> school;
				in >> thesis;
				Emp.push_back(new Researcher(firstname, lastname, salary, school, thesis));
			}
		}

		

		in.close();
	}
}
