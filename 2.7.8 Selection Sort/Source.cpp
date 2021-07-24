#include<iostream>
/*source.cpp Selection Sort

Enter ten unsorted integers...
[0] = 5
[1] = -3
[2] = 2
[3] = 1
[4] = 7
[5] = -9
[6] = 4
[7] = -5
[8] = 6
[9] = -12
Unsorted List = 5, -3, 2, 1, 7, -9, 4, -5, 6, -12,
Sorting...
Sorted List = -12, -9, -5, -3, 1, 2, 4, 5, 6, 7,

*/


using namespace std;


int main()
{
	int  x[10] = { 5, -3, 2, 1, 7, -9, 4, -5, 6, -12 };
	cout << "Enter ten unsorted integers..." << endl;
	//for (auto i = 0; i < 10; i++)
	//{
	//	cout << "[" << i << "] = ";
	//	cin >> x[i];
	//}
	cout << "Unsorted List = ";
	for (auto i = 0; i < 10; ++i)
	{
		if (i == 9)
			cout << x[i] << endl;
		else
			cout << x[i] << ", ";
	}
	//	find smallest change it with the one tha is active
	cout << "Sorting..." << endl;
	for (auto i = 0; i < 10; ++i)
	{
		auto smallest = 0;
		for (auto y = 0; y < 9; ++y)
		{
			if (x[i] < x[y])
			{
				smallest = x[y];
				x[y] = x[i];
				x[i] = smallest;
			}
				

		}

	}
	cout << "Sorted List = ";
	for (auto i = 0; i < 10; ++i)
	{
		if (i == 9)
			cout << x[i] << endl;
		else
			cout << x[i] << ", ";
	}

	return 0;
}