#include<iostream>

using namespace std;

int main()
{
	auto range = 0;
	auto sum = 0;

	cout << "Enter a positive integer to compute the factorial of: ";
	cin >> range;
	sum = range;
	for (auto i = range; i > 0; )
	{
		i--;
		if(i > 0) sum *= i;
		else sum *= 1;
	}
		
	cout << range << "! = " << sum;
	cout << endl;
	return 0;
}