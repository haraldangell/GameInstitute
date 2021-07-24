#include<iostream>


using namespace std;


int main()
{
	auto size = 0;
	auto average = 0;
	cout << "Enter the number of values to average: ";
	cin >> size;

	int range[255];
	for (int i = 0; i < size; ++i)
	{
		cout << "[" << i << "] = ";
		cin >> range[i];
		average += range[i];
	}

	cout << "Average = " << average / size << endl;

	return 0;
}