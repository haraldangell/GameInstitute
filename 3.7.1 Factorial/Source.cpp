#include<iostream>

/*
5! = 120
0! = 1
9! = 362880
3! = 6
Press any key to continue

*/

using namespace std;

int Factorial(int n);
void Print(int number, int sum);


int main()
{
	Print(5, Factorial(5));
	Print(0, Factorial(0));
	Print(9, Factorial(9));
	Print(3, Factorial(3));

	return 0;
}

int Factorial(int n)
{
	auto sum = n;
	if (n == 0)
		sum = 1;
	else
		for (auto i = n; i > 0; )
		{
			i--;

				if (i > 0) sum *= i;
				else sum *= 1;
		}
	return sum;
}
void Print(int number, int sum) 
{
	cout << number << "! = " << sum  << endl;
}