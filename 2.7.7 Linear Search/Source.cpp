#include<iostream>
//source.cpp Linear Search by Harald Angell Aka GoneViking

using namespace std;

/*
List = 7, 3, 32, 2, 55, 34, 6, 13, 29, 22, 11, 9, 1, 5, 42, 39, 8
Enter an integer in the list to search for: 55
Item found at index [4]
Press any key to continue

*/

int main()
{
	int array[] = { 7, 3, 32, 2, 55, 34, 6, 13, 29, 22, 11, 9, 1, 5, 42, 39, 8 };
	auto value = 0;

	cout << "List = ";
	for(auto i = 0; i <= 16; ++i)
	{
		if (i == 16)
			cout << array[i] << endl;
		else
			cout << array[i] << ", ";
	}

	cout << "Enter an integer in the list to search for:";
	cin >> value;
	cout << endl;
	for (auto i = 0; i <= 16; ++i)
	{
		if (array[i] == value)
		{
			cout << "Item found at index [" << i << "]" << endl;
			break;
		}
	}

	return 0;
}