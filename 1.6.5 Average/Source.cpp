#include<iostream>


using namespace std;


int main()
{	
	auto a0 = 0.0f;
	auto a1 = 0.0f;
	auto a2 = 0.0f;
	auto a3 = 0.0f;
	auto a4 = 0.0f;

	cout << "Enter a0: ";
	cin >> a0;
	cout << "Enter a1: ";
	cin >> a1;
	cout << "Enter a2: ";
	cin >> a2;
	cout << "Enter a3: ";
	cin >> a3;
	cout << "Enter a5: ";
	cin >> a4;

	cout << "The average of the five inputs a0...a4 = " << (a0 + a1 + a2 + a3 + a4) / 5 << endl;


	return 0;
}