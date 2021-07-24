#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;


class Print 
{
public:
	void operator()(int t)
	{
		cout << t << " ";
	}
};

class Person {
public:

	Person() { mName = "Default"; mAge = 0; }

	Person(Person* p) { mName = p->mName; mAge = p->mAge; };
	Person(char* name, int age) { mName = name; mAge = age; };
	~Person() {};

	Person SendPerson() const { return *this; };
	void Print() const { cout << mName << endl << "Age :" << mAge << endl; };

	Person operator =(Person& rhs) { Person* p; p->mName = rhs.mName; p->mAge = rhs.mAge; return *p; };

	char* mName;
	int mAge;
};
class People {
public:

	People() { *mName = "Default"; mAge = 0; }

	People(People* p) { mName = p->mName; mAge = p->mAge; };
	People(char* name, int age) { mName = name; mAge = age; };
	~People() {};

	People SendPerson() const { return *this; };
	void Print() const { cout << mName << endl << "Age :" << mAge << endl; };

	People operator =(People& rhs) { People* p; p->mName = rhs.mName; p->mAge = rhs.mAge; return *p; };
	int mAge;
	char* mName;
	
};
template<class T>
void print(T i)
{
	cout << "Testing int: " << i << endl;
}
int main()
{
	void(*test)(string); //Function pointer
	test = print;

	test("Something");

	Person p1("Harald\n", 41);
	People p8("Harald", 41);
	Person p2 = p1.SendPerson();
	p1.Print();
	
	cout << "Person: "<<  sizeof(p1) << " People: " << sizeof(p8) << endl;

	Print pri;

	Person* p = new Person;
	p = &p1.SendPerson();
	cout << "Person after pointer : " << sizeof(p) << endl;
	cout << "Person : " << endl;
	p->Print();
	pri(p->mAge);

	vector<Person*> Persons;	
	cout << " Object: " << &p1 << endl << " Function: " << &p1.SendPerson()<< endl << " Name: " << &p1.mName << endl << " Age: " << &p1.mAge << endl;
	
	Persons.push_back(new Person(p1.SendPerson()));
	Persons.push_back(&p1);
	Persons.push_back(new Person(p1));
	Persons.push_back(&p2);
	Persons.push_back(&p1.SendPerson());

	cout << "Print out of Persons vector " << endl;
	for(int i = 0; i < Persons.size(); ++i)
		Persons[i]->Print();

	srand(time(0));
	vector<int> vecint;
	for(int i = 0; i < 10; ++i)
		vecint.push_back(rand());
	
	for_each(vecint.begin(), vecint.end(), pri);

	int a = 0;
	cin >> a;

	return 0;
}