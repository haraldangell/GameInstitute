#include<iostream>


using namespace std;


int main()
{

	int a[2][3] = { {-5, 2, 8}, {1, 0, 0} };
	int b[2][3] = { {1, 0, 2}, {0, 3, -6} };

	cout << "A = " << endl;
	for (auto i = 0; i < 2; ++i)
	{
		for (auto y = 0; y < 3; ++y)
		{
			cout << a[i][y] << " ";
		}
		cout << endl;
	}
	cout << endl << "B = " << endl;
	for (auto i = 0; i < 2; ++i)
	{
		for (auto y = 0; y < 3; ++y)
		{
			cout << b[i][y] << " ";
		}
		cout << endl;
	}
	cout << endl << "A + B = " << endl;
	for (auto i = 0; i < 2; ++i)
	{
		for (auto y = 0; y < 3; ++y)
		{
			cout << a[i][y] + b[i][y] << " ";
		}
		cout << endl;
	}

	return 0;
}