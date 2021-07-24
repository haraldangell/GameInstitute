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

struct test {
	test();
	test(int a) { this->mA = a; };
	int mA;
};


template<class T>
void print(T i)
{
	cout << "Testing int: " << i << endl;
}
int main()
{
	class person { public: person() { mI = 0; mA = 0; }; person(int i, int a) { mI = i; mA = a; };  int mI, mA; } per(1, 3);
	cout << per.mA << " " << per.mI << endl;
	person test(3,4);
	Print pri;
	pri(2);
	print(1);
	int a = 3;
	int & ref = a;
	string str = "harald";
	print(str);
	return 0;
}