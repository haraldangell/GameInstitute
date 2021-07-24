#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Person
{
public:
	Person();
	Person(string name, int age) { mName = name; mAge = age; };

	string getName() const { return mName; };
	void print() const { cout << "Name: " << mName << endl << "Age: " << mAge <<  endl; };

	void save(ostream& out) const { if (out) { out << mName << " " << mAge; } };
	void savebin(ostream& out) const {if (out) 	{out.write((char*)&mName, 28);//out.write(reinterpret_cast<const char *>(&mAge), 4);
	}};

private:
	string mName;
	int mAge;
};

int main()
{
	vector<Person*> persons;

	cout << "=================================" << endl;

	persons.push_back(new Person("Harald", 41));
	persons.push_back(new Person("Tonia", 35));
	persons.push_back(new Person("Something", 99));

	//for (int i = 0; i < persons.size(); ++i)
	//	persons[i]->print();
	cout << "=================================" << endl;
	string str = "test.txt";
	string strbin = "test.bin";

	//ofstream outFile(str);
	//if (outFile)
	//{	
	//	for (int i = 0; i < persons.size(); ++i)
	//		persons[i]->save(outFile);

	//	outFile.close();
	//}
	ofstream out(strbin, ios_base::binary);
	if (out)
	{
		for (int i = 0; i < persons.size(); ++i)
			out.write((char*)&persons[i]->getName(), 28);
		out.close();
	}
	cout << sizeof(string) << endl;
	//ifstream inFile(str);
	//if (inFile)
	//{
	//	while (!inFile.eof())
	//	{
	//		string name; int age;
	//		inFile >> name >> age;
	//		persons.push_back(new Person(name, age));
	//	}
	//

	//	inFile.close();
	//}
	//cout << "=================================" << endl;
	//cout << "============TEXT=================" << endl;
	//cout << "=================================" << endl;
	//for (int i = 0; i < persons.size(); ++i)
	//	persons[i]->print();
	persons.clear();
	for (int i = 0; i < persons.size(); ++i)
		if (persons.empty() == true)
			cout << "Empty..." << endl;
		else
			persons[i]->print();

	ifstream in(strbin, ios_base::binary);
	if (in)
	{
		for(int i = 0; i < 3; ++i)
		{
			string name; int age;
			in >> name >> age;
			in.read((char*)&name, 2);
			//in.read((char*)&age, 4);
			persons.push_back(new Person(name, 33));
		}

		in.close();
	}
	cout << "=================================" << endl;
	cout << "============Binary===============" << endl;
	cout << "=================================" << endl;
	for (int i = 0; i < persons.size(); ++i)
		persons[i]->print();


	return 0;
}

