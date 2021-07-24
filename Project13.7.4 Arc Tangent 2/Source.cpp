#include<iostream>
#include<cmath>

using namespace std;


const float PI = 3.14f;

float MyArcTangent(float y, float x);

int main()
{
	cout << "MyArcTangent(4, 2) = "   << MyArcTangent(4,2)	  << endl;
	cout << "MyArcTangent(5, -1) = "  << MyArcTangent(5, -1)  << endl;
	cout << "MyArcTangent(-4, -6) = " << MyArcTangent(-4, -6) << endl;
	cout << "MyArcTangent(-6, 4) = "  << MyArcTangent(-6, 4)  << endl;


	return 0;
}
float MyArcTangent(float y, float x)
{
	
	if (x > 0) 
	{
		return	atanf(y / x) * (180 / PI) ;
	}
	else
	{
		return atanf(y / x) * (180 / PI) + 180;
	}
}