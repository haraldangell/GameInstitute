#include <iostream>
#include "Fraction.h"

using namespace std;

/*



float decimal = (float)frac; // convert to decimal;

Overloads the insertion (<<) and extraction (>>) 
operators so that you can output Fractions
with cout and input Fractions with cin.


*/

int main()
{
	cout.setf(ios_base::boolalpha);

	Fraction f(1.0f, 2.0f);
	Fraction g(3.0f, 4.0f);

	cout << "Operator +" << endl;
	Fraction k = f + g;
	k.Print();
	cout << "------------------------------------" << endl;

	cout << "Operator -" << endl;
	k = f - g;
	k.Print();
	cout << "------------------------------------" << endl;

	cout << "Operator *" << endl;
	k = f * g;
	k.Print();
	cout << "------------------------------------" << endl;

	cout << "Operator /" << endl;
	k = f / g;
	k.Print();
	cout << "------------------------------------" << endl;

	bool b;

	//(==, !=, <, >, <=, >=)

	cout << "Operator ==" << endl;
	b = f == g;
	cout << b << endl;
	cout << "------------------------------------" << endl;
	cout << "Operator !=" << endl;
	b = f != g;
	cout << b << endl;
	cout << "------------------------------------" << endl;
	cout << "Operator <" << endl;
	b = f < g;
	cout << b << endl;
	cout << "------------------------------------" << endl;
	cout << "Operator >" << endl;
	b = f > g;
	cout << b << endl;
	cout << "------------------------------------" << endl;
	cout << "Operator <=" << endl;
	b = f <= g;
	cout << b << endl;
	cout << "------------------------------------" << endl;
	cout << "Operator >=" << endl;
	b = f >= g;
	cout << b << endl;
	cout << "------------------------------------" << endl;

	float Decimal = (float)g;

	cout << "Decimal of b is: " << Decimal << endl;

	cout << "------------------------------------" << endl;

	cout << g;
	cout << "------------------------------------" << endl;

	Fraction test;
	cin >> test;
	cout << test;


	return 0;
}