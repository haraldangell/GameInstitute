#include<iostream>


using namespace std;


int main()
{
	auto number = 0.0f;
	auto const PI = 3.14f;

	cout << "Enter the radius of a circle : ";
	cin >> number;
	cout << "The area A of a circle with radius " << number << " = " << PI * (number * number) << endl;
	cout << "The circumference C of a circle with radius " << number << " = " << 2 * PI * number << endl;

	return 0;
}