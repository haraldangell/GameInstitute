#include<iostream>
#include<cmath>

using namespace std;
bool QuadraticFormula(float a, float b, float c, float& r1, float& i1, float& r2, float& i2);

int main()
{
	float a  = 0.0f; 
	float b  = 0.0f; 
	float c  = 0.0f;
	float r1 = 0.0f; 
	float i1 = 0.0f; 
	float r2 = 0.0f; 
	float i2 = 0.0f;


	cout << "Quadratic Equation: y = ax^2 + bx + c" << endl;
	cout << "Quadratic Formula:  x = (-b +/- sqrR(b^2 - 4ac)) / 2a" << endl;

	cout << "Enter a: ";
	cin >> a;
	cout << "Enter b: ";
	cin >> b;
	cout << "Enter c: ";
	cin >> c;
	cout << endl;

	if (!QuadraticFormula(a, b, c, r1, i1, r2, i2))
	{
		// solution contains imaginary
		cout << "Coefficients a=" << a << ", b=" << b << ", c=" << c << " yield S1 = " <<
			r1 << (i1 > 0 ? " + " : " - ") << fabs(i1) << "i, and S2 = " <<
			r2 << (i2 > 0 ? " + " : " - ") << fabs(i2) << "i" << endl;
	}
	else
		cout << "Coefficients a=" << a << ", b=" << b << ", c=" << c << " yield S1 = " << r1 << ", and S2 = " << r2 << endl;

	return 0;
}

bool QuadraticFormula(float a, float b, float c, float & r1, float & i1, float & r2, float & i2)
{
	float QuadRoot = b * b - 4 * a * c;
	if (QuadRoot >= 0.0f)
	{
		r1 = (-b + sqrtf(QuadRoot)) / (2.0f*a);
		r2 = (-b - sqrtf(QuadRoot)) / (2.0f*a);

		i1 = 0.0f;
		i2 = 0.0f;
		return true;
	}
	else
	{
		r1 = -b / (2.0f*a);
		r2 = r1;

		i1 = (sqrtf(-(QuadRoot))) / (2.0f*a);
		i2 = -i1;
		return false;
	}
}
