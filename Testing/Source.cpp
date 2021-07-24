#include <iostream>

using namespace std;

void foo()
{
	static int i = 10;
	cout << (i % 2 == 0 ? ++i : i++);
}

int main()
{
	foo();
	foo();
	foo();
}