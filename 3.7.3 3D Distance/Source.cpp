#include<iostream>
#include<cmath>

/*

Distance between (1, 2, 3) and (0, 0, 0) = 3.74166
Distance between (1, 2, 3) and (1, 2, 3) = 0
Distance between (1, 2, 3) and (7, -4, 5) = 8.7178

*/

using namespace std;

float dist3(float ux, float uy, float uz, float vx, float vy, float vz);




int main()
{
	cout << "Distance between(1, 2, 3) and (0, 0, 0) = " << dist3(1, 2, 3, 0, 0, 0) << endl;
	cout << "Distance between(1, 2, 3) and (1, 2, 3) = " << dist3(1, 2, 3, 1, 2, 3) << endl;
	cout << "Distance between(1, 2, 3) and (7, -4, 5) = " << dist3(1, 2, 3, 7, -4, 5);

	return 0;
}

float dist3(float ux, float uy, float uz, float vx, float vy, float vz)
{
	return sqrtf(((ux - vx)*(ux - vx)) + ((uy - vy)*(uy - vy)) + (uz - vz)*(uz - vz));
}
