#include<iostream>


using namespace std;


int main()
{
	auto n1 = 0.0f;
	auto n2 = 0.0f;

	cout << "Enter a real number n1: ";
	cin >> n1;
	cout << endl;
	cout << "Enter a real number n2: ";
	cin >> n2;
	cout << endl;
	cout << n1 << " + " << n2 << " = " << n1 + n2 << endl;
	cout << n1 << " - " << n2 << " = " << n1 - n2 << endl;
	cout << n1 << " * " << n2 << " = " << n1 * n2 << endl;
	cout << n1 << " / " << n2 << " = " << n1 / n2 << endl;

	return 0;
}